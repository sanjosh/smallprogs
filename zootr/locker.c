#include <zookeeper/zookeeper.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int connected = 0;

void watcher_func(zhandle_t *zh, int type, int state, 
    const char* path, void* watcherCtx)
{
    printf("called type=%d state=%d path=%s\n", type, state, path);
    if (state == ZOO_CONNECTED_STATE) {
       connected = 1; 
    }
}


int main(int argc, char* argv[])
{
    int rc = 0;

    char* host = "127.0.0.1:2181";
    int recv_timeout_ms = 100000;
    clientid_t cid;

    zhandle_t *zh = zookeeper_init(host, watcher_func, recv_timeout_ms, &cid, (void*)1, 0);
    if (zh == NULL) {
        printf("failed to connect\n");
        exit(1);
    }

    while (!connected) {
        printf("waiting for connect\n");
        sleep(1);
    }
    printf("state=%d\n", zoo_state(zh));

    char value[] = "helloworld";
    char *path = "/sandeep";
    char *path_buffer = (char*)malloc(1024);
    rc = zoo_create(zh, path, value, strlen(value), &ZOO_OPEN_ACL_UNSAFE, 0, path_buffer, 1024);
    if (rc != ZOK) {
        printf("create err=%d\n", rc);
    }

    rc = zookeeper_close(zh);
    if (rc != ZOK) {
        printf("close err=%d\n", rc);
    }
}
