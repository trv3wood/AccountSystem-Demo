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

    /// @brief 计算密码哈希值
    /// @param str 用户密码
    /// @param lenMultiplier 哈希值长度倍数
    /// @return 哈希值
    /// @note 使用了SHA256 算法 completed by Z_MAHO
    static std::string hashSHA256(const std::string& str);

    /// @brief 计算用户名的哈希值，用于生成数据文件名
    /// @param str 用户名
    /// @param preferedLen 哈希值长度
    /// @return 指定长度的哈希值
    static std::string hash(const std::string& name, int preferedLen = 8);
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
        OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CONFIG, NULL);
    }

    /// @brief 清理 OpenSSL
    void cleanupOpenSSL() {
        EVP_cleanup();
        ERR_free_strings();
    }
    friend class TestEncryptable;
};
#endif