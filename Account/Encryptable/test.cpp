#include <cassert>
#include <iostream>
#include <string>
#include <gmp.h>
#include <gtest/gtest.h>
#include "encryptable.h"
#include <QtCore/QString>
#include <gmpxx.h>
class TestEncryptable : public bms::Encryptable {
public:
    void encrypt() {
        mp_exp_t exp;
        msg = num.get_str(exp);
        unsigned char ciphertext[1024];
        int ciphertext_len = encryptImpl((unsigned char *)msg.c_str(), msg.size(), key, iv, ciphertext);
        msg = std::string((char *)ciphertext, ciphertext_len);
    }
    void decrypt() {
        unsigned char plaintext[1024];
        int plaintext_len = decryptImpl((unsigned char *)msg.c_str(), msg.size(), key, iv, plaintext);
        msg = std::string((char *)plaintext, plaintext_len);
        num.set_str(msg, 10);
    }
    void testString(const std::string &str) {
        msg = str;
        encrypt();
        decrypt();
        std::cout << "Original: " << str << "\n"
                  << "Encrypted: " << msg << "\n"
                  << "Decrypted: " << num << "\n";
        ASSERT_EQ(str, msg);
    }

    void testHashSHA256(std::string str) {
        std::string hash = hashSHA256(str);
        std::cout << "Original: " << str << "\n"
                  << "Hash: " << hash << "\n";
    }
    std::string msg;
    mpf_class num;
    QString text;
};

void testNum(const mpf_class &num) {
    TestEncryptable test;
    test.num = num;
    test.encrypt();
    std::string encrypted = test.msg;
    test.decrypt();
    mpf_class decrypted = test.num;
    std::cout << "Original: " << num << "\n"
              << "Encrypted: " << encrypted << "\n"
              << "Decrypted: " << decrypted << "\n";
    mp_exp_t exp;
    ASSERT_NE(encrypted, decrypted.get_str(exp));
    ASSERT_EQ(num.get_str(exp), decrypted.get_str(exp));
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

TEST(encryptable, num) {
    mpf_class num("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679");

    testNum(num);
    testNum(num * 2);
    testNum(num / 2);
    testNum(num + 1);
}

TEST(encryptable, text) {
    TestEncryptable test;
    test.text = "Hello, world!";
    test.encrypt();
    std::string encrypted = test.msg;
    test.decrypt();
    QString decrypted = test.text;
    std::cout << "Original: " << test.text.toStdString() << "\n"
              << "Encrypted: " << encrypted << "\n"
              << "Decrypted: " << decrypted.toStdString() << "\n";
    ASSERT_EQ(test.text, decrypted);
    test.testString("Manba out!");
}

TEST(encryptable, hashSHA256) {
    TestEncryptable test;
    test.testHashSHA256("Hello, world!");
}