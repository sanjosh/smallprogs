/**
 * gcc <prog.c> -libverbs 
 */

#include <infiniband/verbs.h>
#include <assert.h> // assert
#include <stdlib.h> // malloc
#include <stdbool.h> // bool

#define MAX_SEND_WR 1
#define MAX_RECV_WR 1
#define MAX_INLINE 256
#define IB_PHYS_PORT 1

int main(int argc, char* argv[])
{
    int rc = 0;
    int num_devices = 0;
    struct ibv_device **dev_list_array = ibv_get_device_list(&num_devices);
    assert(dev_list_array);
    assert(num_devices);
   
    struct ibv_context *ctx = ibv_open_device(dev_list_array[0]);
    assert(ctx);

    struct ibv_pd *pd = ibv_alloc_pd(ctx);
    assert(pd);

    int num_cqe = MAX_SEND_WR;
    void* cq_ctx = NULL;
    struct ibv_comp_channel *comp_channel = NULL;
    int comp_vector = 0;
    struct ibv_cq *cq = ibv_create_cq(ctx, num_cqe, cq_ctx, comp_channel, comp_vector);
    assert(cq);

    struct ibv_qp_init_attr dgram_qp_init_attr = {
        .send_cq = cq,
        .recv_cq = cq,
        .srq     = NULL,
        .cap = {
            .max_send_wr = MAX_SEND_WR,
            .max_recv_wr = MAX_RECV_WR,
            .max_send_sge = 1,
            .max_recv_sge = 1,
            .max_inline_data = MAX_INLINE
        },
        .qp_type = IBV_QPT_UD, // IBV_QPT_RC or IBV_QPT_UC
        .sq_sig_all = false
    };
    struct ibv_qp *dgram_qp = ibv_create_qp(pd, &dgram_qp_init_attr);
    assert(dgram_qp);

    struct ibv_qp_attr dgram_attr = {
        .qp_state = IBV_QPS_INIT,
        .pkey_index = 0,
        .port_num = IB_PHYS_PORT,
        .qkey = 0x11111111 // only for UD
    };

    // transition QP to init state
    rc = ibv_modify_qp(dgram_qp, &dgram_attr, IBV_QP_STATE | IBV_QP_PKEY_INDEX | IBV_QP_PORT | IBV_QP_QKEY);
    assert(rc != 0);

    // register mem region
    int access_flags = IBV_ACCESS_LOCAL_WRITE | IBV_ACCESS_REMOTE_READ | IBV_ACCESS_REMOTE_WRITE;
    size_t mr_size = 4096;
    void* mr_addr = malloc(mr_size);
    struct ibv_mr *mr = ibv_reg_mr(pd, mr_addr, mr_size, access_flags);
    assert(mr);

    // lkey = mr->lkey;
    //
    // server must call ib_create_ah for every client UD QP
    //
    struct ibv_qp_attr dgram_rtr_attr = {
        .qp_state = IBV_QPS_RTR,
    };

    // move UD to RTR
    rc = ibv_modify_qp(dgram_qp, &dgram_rtr_attr, IBV_QP_STATE);
    assert(rc != 0);

    struct ibv_qp_attr dgram_rts_attr = {
        .qp_state = IBV_QPS_RTS,
        .sq_psn   = 0 // TODO
    };

    // move UD to RTS
    rc = ibv_modify_qp(dgram_qp, &dgram_rtr_attr, IBV_QP_STATE | IBV_QP_SQ_PSN);
    assert(rc != 0);

    struct ibv_wc wc;
    int num_comps = ibv_poll_cq(cq, 1, &wc);
    rc = ibv_dereg_mr(mr);
    assert(rc != 0);

    rc = ibv_destroy_qp(dgram_qp);
    assert(rc != 0);

    rc = ibv_destroy_cq(cq);
    assert(rc != 0);
    
    rc = ibv_dealloc_pd(pd);
    assert(rc != 0);
    rc = ibv_close_device(ctx);
    assert(rc != 0);
    
    ibv_free_device_list(dev_list_array);
}
