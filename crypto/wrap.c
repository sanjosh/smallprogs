
/*
 * gcc wrap.c -lcrypto -g -lasan -fsanitize=address -fuse-ld=gold
 */

#include <unistd.h> // write
#include <stdlib.h> // malloc
#include <string.h> // strlen
#include <assert.h> // assert
#include <stdio.h> // printf
#include <openssl/aes.h>
#include <openssl/rand.h> // RAND_bytes

// RFC 3394
// https://github.com/Netflix/NfWebCrypto/blob/master/crypto/AesKeyWrapper.cpp
//
// http://openssl.6102.n7.nabble.com/AES-Key-Wrap-in-FIPS-Mode-td50238.html
//
// https://www.openssl.org/docs/fipsnotes.html
//
// https://news.ycombinator.com/item?id=7635221

int main(int argc, char* argv[])
{
#define DEK_SIZE 128
#define KEK_SIZE 128


    unsigned char keyToWrap[DEK_SIZE];
    unsigned char wrappedKey[DEK_SIZE + 8];
    unsigned char unwrappedKey[DEK_SIZE];
    unsigned char metaKey[KEK_SIZE];
    unsigned char input_iv[100];
    unsigned char output_iv[100];
    AES_KEY keyEncryptionKey;

    RAND_bytes(&metaKey[0], KEK_SIZE);
    RAND_bytes(&keyToWrap[0], DEK_SIZE);
    bzero(unwrappedKey, DEK_SIZE);
    bzero(wrappedKey, DEK_SIZE + 8);

    // data key must be protected by kek of equal or greater strength
    assert(KEK_SIZE >= DEK_SIZE);

    {
        char* iv = NULL;
        AES_set_encrypt_key((const unsigned char*)metaKey, KEK_SIZE, &keyEncryptionKey);
        AES_wrap_key(&keyEncryptionKey, iv, wrappedKey, keyToWrap, DEK_SIZE);
    }

    {
        char* iv = NULL;
        AES_set_decrypt_key((const unsigned char*)metaKey, KEK_SIZE, &keyEncryptionKey);
        AES_unwrap_key(&keyEncryptionKey, iv, unwrappedKey, wrappedKey, DEK_SIZE + 8);
    
    }

    int key_equal = memcmp(keyToWrap, unwrappedKey, DEK_SIZE);
    printf("equal=%d\n", (key_equal == 0));
}
