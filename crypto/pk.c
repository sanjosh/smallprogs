
/*
 * gcc pk.c -lcrypto
 */

#include <unistd.h> // write
#include <stdlib.h> // malloc
#include <ctype.h> // isprint
#include <stdio.h> // ptinf
#include <string.h> // strlen
#include <openssl/evp.h>

typedef struct cipher_type {
    int default_key_len;
}cipher_type;

cipher_type aes_cbc_256_cipher = {
    .default_key_len = 256
};

#define DUMP_COLS 20

void hexdump(char* buf, size_t buflen)
{
    const int extra = (buflen % DUMP_COLS) ? (DUMP_COLS - (buflen % DUMP_COLS)) : 0;
    int tlen = buflen + extra;
    for (int i = 0; i < tlen; i ++) {
        if (i % DUMP_COLS == 0) {
            printf("0x%06x: ", i);
        }
        if (i < buflen) {
            printf("%02x ", 0xFF & buf[i]);
        } else {
            printf(" ");
        }

        // if this is the 19th char
        if (i % DUMP_COLS == DUMP_COLS - 1) {
            putchar('\n');
            printf("         ");
            for (int j = i - (DUMP_COLS - 1); j <= i; j++) {
                if (j >= buflen) {
                    putchar(' ');
                } else if (isprint(buf[j])) {
                    putchar(0xFF & buf[j]);
                } else {
                    putchar('.');
                }
            }
            putchar('\n');
        }
    }
}

int main(int argc, char* argv[])
{
    const char* passwd = "abcdefgh";
    if (argc > 1) {
        passwd = argv[1];
    }
    const char* salt = "saltpeanuts";
    unsigned char* out = (unsigned char*)malloc(aes_cbc_256_cipher.default_key_len);
    int pbkdf_num_iterations = 8192;

    // change salt.  in gcsfs, it is bucket name
    PKCS5_PBKDF2_HMAC_SHA1(passwd, strlen(passwd),
            salt, strlen(salt),
            pbkdf_num_iterations, 
            aes_cbc_256_cipher.default_key_len,
            out);

    hexdump(out, aes_cbc_256_cipher.default_key_len);

    free(out);
}
