#ifndef ENCRYPTABLE_H
#define ENCRYPTABLE_H
#include <openssl/aes.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <QtCore/QString>

namespace bms {
class Encryptable;
}
class bms::Encryptable {
public:
    /// @brief 密钥
    static unsigned char* key;
    /// @brief 初始化向量
    static unsigned char* iv;

    virtual ~Encryptable() {
        cleanupOpenSSL();
    }
    Encryptable() {
        initOpenSSL();
    }
protected:
    /// @brief 加密实现
    /// @param plaintext 明文
    /// @param plaintext_len 明文长度
    /// @param key 密钥
    /// @param iv 初始化向量
    /// @param ciphertext 密文
    /// @return 密文长度
    static int encryptImpl(unsigned char *plaintext, int plaintext_len,
                    unsigned char *key, unsigned char *iv,
                    unsigned char *ciphertext);
    /// @brief 解密实现
    /// @param ciphertext 密文
    /// @param ciphertext_len 密文长度
    /// @param key 密钥
    /// @param iv 初始化向量
    /// @param plaintext 明文
    static int decryptImpl(unsigned char *ciphertext, int ciphertext_len,
                    unsigned char *key, unsigned char *iv,
                    unsigned char *plaintext);
private:
    /// @brief 处理错误
    static void handleErrors(void) {
        ERR_print_errors_fp(stderr);
        abort();
    }

    /// @brief 初始化 OpenSSL
    void initOpenSSL() {
        ERR_load_crypto_strings();
        OpenSSL_add_all_algorithms();
        OPENSSL_config(NULL);
    }

    /// @brief 清理 OpenSSL
    void cleanupOpenSSL() {
        EVP_cleanup();
        ERR_free_strings();
    }
    friend class TestEncryptable;
};
#endif