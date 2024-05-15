#ifndef ENCRYPTABLE_H
#define ENCRYPTABLE_H
#include <openssl/aes.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>

namespace bms {
class Encryptable;
}
class bms::Encryptable {
public:
    virtual void encrypt() = 0;
    virtual void decrypt() = 0;
    static unsigned char* key;
    static unsigned char* iv;

    virtual ~Encryptable() {
        cleanupOpenSSL();
    }
    Encryptable() {
        initOpenSSL();
    }
protected:
    int encryptImpl(unsigned char *plaintext, int plaintext_len,
                    unsigned char *key, unsigned char *iv,
                    unsigned char *ciphertext);
    int decryptImpl(unsigned char *ciphertext, int ciphertext_len,
                    unsigned char *key, unsigned char *iv,
                    unsigned char *plaintext);
private:
    void handleErrors(void) {
        ERR_print_errors_fp(stderr);
        abort();
    }

    void initOpenSSL() {
        ERR_load_crypto_strings();
        OpenSSL_add_all_algorithms();
        OPENSSL_config(NULL);
    }

    void cleanupOpenSSL() {
        EVP_cleanup();
        ERR_free_strings();
    }
};
#endif