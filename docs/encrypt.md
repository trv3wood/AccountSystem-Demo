为了确保用户信息的安全，尤其是在涉及敏感数据如银行卡号和个人信息时，使用加密技术是非常重要的。下面是一个简单的流程，展示如何在C++中加密和解密用户信息。

### 1. 选择加密算法
- **对称加密**：如AES（高级加密标准）。它快速且适合大多数需要加密和解密的场景。
- **非对称加密**：如RSA。它适合在需要公钥加密和私钥解密的场景，但通常比对称加密慢。

### 2. 使用加密库
C++本身没有内置的加密库，但可以使用第三方库，如OpenSSL或Crypto++。

#### 使用OpenSSL库

##### 1. 安装OpenSSL
确保你安装了OpenSSL库，并将其包含在你的项目中。

##### 2. 引入OpenSSL头文件
在你的C++代码中引入必要的头文件：
```cpp
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
```

##### 3. 初始化和清理OpenSSL
在程序开始时初始化OpenSSL，在结束时清理资源。
```cpp
void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

void initOpenSSL()
{
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);
}

void cleanupOpenSSL()
{
    EVP_cleanup();
    ERR_free_strings();
}
```

##### 4. 加密函数
下面是一个使用AES对称加密的示例函数：
```cpp
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    /* Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /* Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /* Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}
```

##### 5. 解密函数
对应的解密函数如下：
```cpp
int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    /* Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits */
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /* Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    /* Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}
```

### 3. 示例代码
以下是一个完整的示例代码，展示如何加密和解密用户信息：
```cpp
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <string>
#include <iostream>
#include <cstring>

void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

void initOpenSSL()
{
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);
}

void cleanupOpenSSL()
{
    EVP_cleanup();
    ERR_free_strings();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

int main()
{
    // 初始化OpenSSL
    initOpenSSL();

    // 256 bit key
    unsigned char *key = (unsigned char *)"01234567890123456789012345678901";
    // 128 bit IV
    unsigned char *iv = (unsigned char *)"0123456789012345";

    // 明文
    unsigned char *plaintext = (unsigned char *)"Sensitive user information.";

    // 缓冲区
    unsigned char ciphertext[128];
    unsigned char decryptedtext[128];

    int decryptedtext_len, ciphertext_len;

    // 加密
    ciphertext_len = encrypt(plaintext, strlen((char *)plaintext), key, iv,
                             ciphertext);

    std::cout << "Ciphertext is:" << std::endl;
    BIO_dump_fp(stdout, (const char *)ciphertext, ciphertext_len);

    // 解密
    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv,
                                decryptedtext);

    // 添加NULL终止符
    decryptedtext[decryptedtext_len] = '\0';

    std::cout << "Decrypted text is:" << std::endl;
    std::cout << decryptedtext << std::endl;

    // 清理OpenSSL
    cleanupOpenSSL();

    return 0;
}
```

### 总结
通过使用OpenSSL库，你可以轻松地加密和解密用户信息，确保数据的安全性。在实际应用中，确保密钥管理安全，避免硬编码密钥，并在生产环境中使用安全的密钥存储和管理策略。