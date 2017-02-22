#pragma once

#include <unistd.h> // off_t 

#define MEK_LENGTH 256
#define KEK_LENGTH 256
#define WKEK_LENGTH (KEK_LENGTH + 8)
#define DEK_LENGTH 256
#define WDEK_LENGTH (DEK_LENGTH + 8)

typedef char MEK[MEK_LENGTH];
typedef char KEK[KEK_LENGTH];
typedef char WKEK[WKEK_LENGTH];
typedef char DEK[DEK_LENGTH];
typedef char WDEK[WDEK_LENGTH];

int dce_crypt_init();
int dce_crypt_destroy();

int dce_mek_generate(const char* passwd, MEK mek);
int dce_kek_generate(KEK key);
int dce_dek_generate(DEK key);

int dce_encrypt_kek(MEK metaKey, KEK keyToWrap, WKEK wrappedKey);
int dce_decrypt_kek(MEK metaKey, WKEK wrappedKey, KEK unwrappedKey);

int dce_encrypt_dek(KEK kek, DEK keyToWrap, WDEK wrappedKey);
int dce_decrypt_dek(KEK kek, WDEK wrappedKey, DEK unwrappedKey);

int dce_encrypt_data(DEK dataKey, char* in_data, off_t offset, size_t size, char* out_data);
int dce_decrypt_data(DEK dataKey, char* in_data, off_t offset, size_t size, char* out_data);
