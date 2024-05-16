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
    /// @brief 加密函数
    /// @note 用于加密用户信息
    /// @note TODO: 利用 encryptImpl() 实现加密
    virtual void encrypt() = 0;
    /// @brief 解密函数
    /// @note 用于解密用户信息
    /// @note TODO: 利用 decryptImpl() 实现解密
    virtual void decrypt() = 0;
    
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
    int encryptImpl(unsigned char *plaintext, int plaintext_len,
                    unsigned char *key, unsigned char *iv,
                    unsigned char *ciphertext);
    /// @brief 解密实现
    /// @param ciphertext 密文
    /// @param ciphertext_len 密文长度
    /// @param key 密钥
    /// @param iv 初始化向量
    /// @param plaintext 明文
    int decryptImpl(unsigned char *ciphertext, int ciphertext_len,
                    unsigned char *key, unsigned char *iv,
                    unsigned char *plaintext);
private:
    /// @brief 处理错误
    void handleErrors(void) {
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
};
#endif