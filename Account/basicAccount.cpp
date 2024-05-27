#include "basicAccount.h"

#include <gmpxx.h>

#include <QString>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "account.h"

namespace bms {
const unsigned BasicAccount::transferRestriction = 5000;

void BasicAccount::transfer(Account* to, const mpf_class& amount) {
    if (amount > transferRestriction) {
        std::cerr << "Transfer amount exceeds the restriction." << '\n';
        return;
    }
    Account::transfer(to, amount);
}

void BasicAccount::serialize(std::string& data) const {
    data.clear();
    // 将数据序列化为字符串，以便存储，用'\n'分隔
    data += m_name + '\n' + m_passwd + '\n' + m_phonenumber + '\n' + m_id + '\n' + m_cardNumber + '\n' + mpf_class2str(m_balance) + '\n' + mpf_class2str(m_interestRate) + '\n';
}

void BasicAccount::deserialize(const std::string& data) {
    // 解析用'\n'分隔的字符串，恢复数据
    std::istringstream iss(data);
    std::getline(iss, m_name);
    std::getline(iss, m_passwd);
    std::getline(iss, m_phonenumber);
    std::getline(iss, m_id);
    std::getline(iss, m_cardNumber);
    std::string balance, interestRate;
    std::getline(iss, balance);
    std::getline(iss, interestRate);
    m_balance = balance;
    m_interestRate = interestRate;
}

BasicAccount::BasicAccount(const std::string& name, const std::string& passwd,
             const std::string& phoneNum, const std::string& id)
    : Account(name, hashSHA256(passwd), phoneNum, id) {
    m_balance = 0;
    m_interestRate = defualtInterestRate;
    m_datafile = hash(m_phonenumber, 8) + ".dat";
}

void BasicAccount::store(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Cannot open file for writing");
    }

    std::string data;
    serialize(data);

    int ciphertext_len = data.size() + EVP_MAX_BLOCK_LENGTH;
    unsigned char* ciphertext = new unsigned char[ciphertext_len];
    ciphertext_len = encryptImpl((unsigned char*)data.c_str(), data.size(), key, iv, ciphertext);

    outFile.write(reinterpret_cast<const char*>(&ciphertext_len), sizeof(ciphertext_len));
    outFile.write(reinterpret_cast<const char*>(ciphertext), ciphertext_len);

    delete[] ciphertext;
    outFile.close();
}  

void BasicAccount::load(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Cannot open file for reading");
    }

    int ciphertext_len;
    inFile.read(reinterpret_cast<char*>(&ciphertext_len), sizeof(ciphertext_len));

    unsigned char* ciphertext = new unsigned char[ciphertext_len];
    inFile.read(reinterpret_cast<char*>(ciphertext), ciphertext_len);

    unsigned char* plaintext = new unsigned char[ciphertext_len + EVP_MAX_BLOCK_LENGTH];
    int plaintext_len = decryptImpl(ciphertext, ciphertext_len, key, iv, plaintext);

    std::string data((char*)plaintext, plaintext_len);
    deserialize(data);

    delete[] ciphertext;
    delete[] plaintext;
    inFile.close();
}
}// namespace bms
