#include "basicAccount.h"

#include <gmpxx.h>
#include <qlist.h>

#include <QFile>
#include <QMessageBox>
#include <QString>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "account.h"

namespace bms {
const unsigned BasicAccount::transferRestriction = 5000;

void BasicAccount::transfer(Account* to, const mpf_class& amount) {
    if (amount > transferRestriction) {
#if ACCOUNT_DEBUG == 1
        std::cerr << "Transfer amount exceeds the restriction." << '\n';
#endif
        QMessageBox::warning(nullptr, "限额", "转账金额超过限制 5000 元");
        return;
    }
    Account::transfer(to, amount);
}

void BasicAccount::transfer(const QString& phone, const QString& amount) {
    // 同步转出账户信息
    load();
    BasicAccount to(phone.toStdString(), ".");
    // 检查转入账户是否存在
    if (!QFile(to.datafile().c_str()).exists()) {
        QMessageBox::warning(nullptr, "不存在", "转入账户不存在");
        return;
    }
    // 同步转入账户信息
    to.load();
    transfer(&to, mpf_class(amount.toStdString()));
}

void BasicAccount::serialize(std::string& data) const {
    data.clear();
    // 将数据序列化为字符串，以便存储，用'\n'分隔
    data += m_name + '\n' + m_passwd + '\n' + m_phonenumber + '\n' + m_id +
            '\n' + m_cardNumber + '\n' + mpf_class2str(m_balance) + '\n' +
            mpf_class2str(m_interestRate) + '\n';
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
    m_datafile = hash(m_phonenumber, 8) + ".dat";
    m_logfile = hash(m_phonenumber, 8) + ".log";
}

BasicAccount::BasicAccount(const std::string& name, const std::string& passwd,
                           const std::string& phoneNum, const std::string& id)
    : Account(name, hashSHA256(passwd), phoneNum, id) {
    m_datafile = hash(m_phonenumber, 8) + ".dat";
    m_logfile = hash(m_phonenumber, 8) + ".log";
}

BasicAccount::BasicAccount(const std::string& phoneNum,
                           const std::string& passwd)
    : Account(phoneNum, passwd) {
    m_datafile = hash(m_phonenumber, 8) + ".dat";
    m_logfile = hash(m_phonenumber, 8) + ".log";
}

void BasicAccount::store(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary | std::ios::trunc);
    if (!outFile) {
        throw std::runtime_error(__FILE__ + std::string(":") +
                                 std::to_string(__LINE__) +
                                 std::string(" on ") + __PRETTY_FUNCTION__ +
                                 "Cannot open file for writing");
    }

    std::string data;
    serialize(data);

    int ciphertext_len = data.size() + EVP_MAX_BLOCK_LENGTH;
    unsigned char* ciphertext = new unsigned char[ciphertext_len];
    ciphertext_len = encryptImpl((unsigned char*)data.c_str(), data.size(), key,
                                 iv, ciphertext);

    outFile.write(reinterpret_cast<const char*>(&ciphertext_len),
                  sizeof(ciphertext_len));
    outFile.write(reinterpret_cast<const char*>(ciphertext), ciphertext_len);

    delete[] ciphertext;
    outFile.close();
}

void BasicAccount::store() { store(m_datafile); }

void BasicAccount::load(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Cannot open file for reading");
    }

    int ciphertext_len;
    inFile.read(reinterpret_cast<char*>(&ciphertext_len),
                sizeof(ciphertext_len));

    unsigned char* ciphertext = new unsigned char[ciphertext_len];
    inFile.read(reinterpret_cast<char*>(ciphertext), ciphertext_len);

    unsigned char* plaintext =
        new unsigned char[ciphertext_len + EVP_MAX_BLOCK_LENGTH];
    int plaintext_len =
        decryptImpl(ciphertext, ciphertext_len, key, iv, plaintext);

    std::string data((char*)plaintext, plaintext_len);
    deserialize(data);

    delete[] ciphertext;
    delete[] plaintext;
    inFile.close();
}

void BasicAccount::load() { load(m_datafile); }

void BasicAccount::setPasswd(const std::string& passwd) {
    m_passwd = hashSHA256(passwd);
}

void BasicAccount::deposit(const QString& amount) {
    load();
    Account::deposit(amount);
}

void BasicAccount::withdraw(const QString& amount) {
    load();
    Account::withdraw(amount);
}

QStringList BasicAccount::recentRecords() const {
    QFile logFile(QString::fromStdString(m_logfile));
    if (!logFile.open(QIODevice::ReadOnly)) {
        // 如果日志文件不存在，返回空列表
        return QStringList();
    }
    QString log = logFile.readAll();
    logFile.close();
    // 取最近的10条记录
    QStringList records = log.split('\n');
    int n = records.size();
    if (n > 10) {
        records = records.mid(n - 10);  // 取最后10条记录
    }
#if ACCOUNT_DEBUG == 1
    for (const auto& record : records) {
        qDebug() << record;
    }
#endif
    if (records.back() == "") {
        records.pop_back();  // 去掉最后一个空行
    }
    // 翻转顺序
    std::reverse(records.begin(), records.end());
    return records;
}

QStringList BasicAccount::recentTransfers() const {
    QStringList records = recentRecords();
    QStringList transfers(" ");
    for (const auto& record : records) {
        if (record.contains("转账") || record.contains("收款")) {
            // 截取"对方"后的字符串
            transfers.append(record.mid(record.indexOf("对方: ") + 4));
        }
    }
    // 去重
    transfers.removeDuplicates();
#if ACCOUNT_DEBUG == 1
    qDebug() << "Transfers: " << transfers;
#endif
    return transfers;
}
}  // namespace bms
