#include "dce_crypt.h"

#include <openssl/evp.h> // pbkdf
#include <openssl/aes.h> // wrap
#include <openssl/rand.h> // RAND_bytes
#include <openssl/ssl.h> // init
#include <openssl/err.h> // init
#include <openssl/conf.h> // init

#include <string.h>

/**
 * https://en.wikibooks.org/wiki/OpenSSL/Initialization
 */
int dce_crypt_init()
{
    ERR_load_crypto_strings(); // libcrypto
    OpenSSL_add_all_algorithms(); // libcrypto
    OPENSSL_config(NULL);
    return 0;
}

int dce_crypt_destroy()
{
    ERR_free_strings();
    RAND_cleanup();
    EVP_cleanup ();
    CONF_modules_free();
    ERR_remove_state(0);
    return 0;
}

int dce_mek_generate(const char* passwd, MEK mek)
{
    const char* salt = "saltpeanuts";
    int pbkdf_num_iterations = 8192;

    // TODO change salt.  
    int ret = PKCS5_PBKDF2_HMAC_SHA1(passwd, strlen(passwd),
            salt, strlen(salt),
            pbkdf_num_iterations, 
            sizeof(MEK),
            mek);

    if (ret != 1) {  
        // ("password based key derivation failed");
    }

    return ret;
}

int dce_kek_generate(KEK key)
{
    RAND_bytes(key, sizeof(KEK));
	return 0;
}

int dce_dek_generate(DEK key)
{
    RAND_bytes(key, sizeof(DEK));
	return 0;
}

int dce_encrypt_kek(MEK metaKey, KEK keyToWrap, WKEK wrappedKey)
{
    AES_KEY keyEncryptionKey;
    char* iv = NULL;
    int ret = 0;
    int rc = 0;

    ret = AES_set_encrypt_key((const unsigned char*)metaKey, sizeof(MEK), &keyEncryptionKey);
    if (ret != 0) {
        rc = EINVAL;
    }

    ret = AES_wrap_key(&keyEncryptionKey, iv, wrappedKey, keyToWrap, sizeof(KEK));
    if (ret != sizeof(WKEK)) {
        rc = EINVAL;
    }
    return rc;
}

int dce_decrypt_kek(MEK metaKey, WKEK wrappedKey, KEK unwrappedKey)
{
    AES_KEY keyEncryptionKey;
    char* iv = NULL;
    int ret = 0;
    int rc = 0;

    ret = AES_set_decrypt_key((const unsigned char*)metaKey, sizeof(MEK), &keyEncryptionKey);
    if (ret != 0) {
        rc = EINVAL;
    }
    ret = AES_unwrap_key(&keyEncryptionKey, iv, unwrappedKey, wrappedKey, sizeof(WKEK));
    if (ret != sizeof(KEK)) {
        rc = EINVAL;
    }
    return rc;
}

int dce_encrypt_dek(KEK metaKey, DEK keyToWrap, WDEK wrappedKey)
{
    AES_KEY keyEncryptionKey;
    char* iv = NULL;
    int ret = 0;
    int rc = 0;

    ret = AES_set_encrypt_key((const unsigned char*)metaKey, sizeof(KEK), &keyEncryptionKey);
    if (ret != 0) {
        rc = EINVAL;
    }
    ret = AES_wrap_key(&keyEncryptionKey, iv, wrappedKey, keyToWrap, sizeof(DEK));
    if (ret != sizeof(WDEK)) {
        rc = EINVAL;
    }
    return rc;
}

int dce_decrypt_dek(KEK metaKey, WKEK wrappedKey, KEK unwrappedKey)
{
    AES_KEY keyEncryptionKey;
    char* iv = NULL;
    int ret = 0;
    int rc = 0;

    ret = AES_set_decrypt_key((const unsigned char*)metaKey, sizeof(KEK), &keyEncryptionKey);
    if (ret != 0) {
        rc = EINVAL;
    }
    ret = AES_unwrap_key(&keyEncryptionKey, iv, unwrappedKey, wrappedKey, sizeof(WDEK));
    if (ret != sizeof(DEK)) {
        rc = EINVAL;
    }
    return rc;
}

static const size_t MAX_IV_LEN = 16;

int dce_encrypt_data(DEK data_key, char* in_data, off_t offset, size_t size, char* out_data)
{
    int ret = 0;
    int rc = 0;
    const EVP_CIPHER* cipher = NULL;

    // XTS requires IV; the input offset is dividing by 64k, so its 6 bytes max
    // and that requires (6 * 2.5) bytes which is why 16 bytes allocated here
    unsigned char iv[MAX_IV_LEN]; 
    snprintf(iv, MAX_IV_LEN, "%ld", offset);

    int updated = 0;
    int finalized = 0;

    cipher = EVP_aes_256_xts();

    EVP_CIPHER_CTX* ctxptr = EVP_CIPHER_CTX_new();

    ret = EVP_EncryptInit_ex(ctxptr, cipher, NULL, data_key, iv);
    if (ret != 1) {
        rc = EINVAL;
    }

    //EVP_CIPHER_CTX_set_padding(ctxptr, 0);

    ret = EVP_EncryptUpdate(ctxptr, &out_data[0], &updated, in_data, size); // returns 1
    if (ret != 1) {
        rc = EINVAL;
    }

    ret = EVP_EncryptFinal_ex(ctxptr, &out_data[updated], &finalized); // returns 1
    if (ret != 1) {
        rc = EINVAL;
    }

    EVP_CIPHER_CTX_free(ctxptr);


    return rc;
}

int dce_decrypt_data(DEK data_key, char* in_data, off_t offset, size_t size, char* out_data)
{
    int ret = 0;
    int rc = 0;
    const EVP_CIPHER* cipher = NULL;

    // XTS requires IV; the input offset is dividing by 64k, so its 6 bytes max
    // and that requires (6 * 2.5) bytes which is why 16 bytes allocated here
    unsigned char iv[MAX_IV_LEN]; 
    snprintf(iv, MAX_IV_LEN, "%ld", offset);
    int updated = 0;
    int finalized = 0;

    cipher = EVP_aes_256_xts();
    EVP_CIPHER_CTX* ctxptr = EVP_CIPHER_CTX_new();

    ret = EVP_DecryptInit_ex(ctxptr, cipher, NULL, data_key, iv);
    if (ret != 1) {
        rc = EINVAL;
    }
    
    //EVP_CIPHER_CTX_set_padding(ctxptr, 0);

    ret = EVP_DecryptUpdate(ctxptr, &out_data[0], &updated, in_data, size);
    if (ret != 1) {
        rc = EINVAL;
    }

    ret = EVP_DecryptFinal_ex(ctxptr, &out_data[updated], &finalized);
    if (ret != 1) {
        rc = EINVAL;
    }

    EVP_CIPHER_CTX_free(ctxptr);


    return rc;
}
