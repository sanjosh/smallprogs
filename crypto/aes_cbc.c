/*
 * gcc aes_cbc.c -lcrypto -fsanitize=address -lasan -fuse-ld=gold -g
 */
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdio.h>

#define DATA_LEN 4096
#define KEY_LEN 256

int main(int argc, char* argv[])
{
    const EVP_CIPHER* cipher = NULL;

    int mode = 0;
    unsigned char key[KEY_LEN];
    // XTS requires IV
    unsigned char iv[16] = "abcdefghijklmnop";
    unsigned char in[DATA_LEN];
    unsigned char in_decoded[DATA_LEN];
    unsigned char out[DATA_LEN];
    int updated;
    int finalized;
    size_t size = DATA_LEN;

    memset(in, 'a', DATA_LEN);
    bzero(in_decoded, DATA_LEN);

    RAND_bytes(&key[0], KEY_LEN);

    cipher = EVP_aes_256_xts();
    //cipher = EVP_aes_256_cbc();

    {
        EVP_CIPHER_CTX* ctxptr = EVP_CIPHER_CTX_new();

        EVP_EncryptInit_ex(ctxptr, cipher, NULL, key, iv);

        printf("%d\n", EVP_CIPHER_CTX_iv_length(ctxptr));
        
        //EVP_CIPHER_CTX_set_padding(ctxptr, 0);

        EVP_EncryptUpdate(ctxptr, &out[0], &updated, in, size); // returns 1

        EVP_EncryptFinal_ex(ctxptr, &out[updated], &finalized); // returns 1

        EVP_CIPHER_CTX_free(ctxptr);
    } 
    {
        EVP_CIPHER_CTX* ctxptr = EVP_CIPHER_CTX_new();

        EVP_DecryptInit_ex(ctxptr, cipher, NULL, key, iv);
        
        //EVP_CIPHER_CTX_set_padding(ctxptr, 0);

        EVP_DecryptUpdate(ctxptr, &in_decoded[0], &updated, out, size);

        EVP_DecryptFinal_ex(ctxptr, &in_decoded[updated], &finalized);

        EVP_CIPHER_CTX_free(ctxptr);
    }

    int buf_equal = memcmp(in, in_decoded, DATA_LEN);
    printf("%d\n", (buf_equal == 0));



}
