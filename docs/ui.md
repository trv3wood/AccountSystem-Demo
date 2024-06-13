# UI 界面的实现
## QML 语言与 C++ 的交互
QML 是一种基于 JavaScript 的声明式语言，用于设计用户界面。它是 Qt Quick 的一部分，是一种专门用于设计用户界面的语言。QML 通过声明式语法，可以更加方便地实现用户界面的设计。同时可以方便地与 C++ 代码进行交互，实现更加复杂的功能。

## 信号与槽机制
QML 与 C++ 之间的交互主要通过信号与槽机制实现。在 QML 中，可以通过 `signal` 关键字声明一个信号，通过 `on` 关键字连接信号与槽。在 C++ 中，可以通过 `Q_INVOKABLE` 关键字声明一个槽，通过 `connect` 函数连接信号与槽。

## 动态绑定
QML 中的属性可以通过动态绑定的方式实现。动态绑定是指，当一个属性的值发生变化时，与之绑定的其他属性也会随之变化。动态绑定是基于信号与槽机制实现的，它可以方便地实现用户界面的交互效果.
```qml
RoundButton {
    text: "存款"
    font.pixelSize: 35
    font.family: "Microsoft YaHei"
    radius: height / 2 - 10
    width: 600
    height: 80
    background: Rectangle {
        color: "lightgreen"
        radius: parent.radius
        anchors.fill: parent
    }
    onClicked: { // 点击事件
        if (deposit.amount === "") {
            return
        }
        var amount = deposit.amount
        if (isNaN(amount)) {
            return
        }
        user.deposit(amount); // 调用 C++ 函数
        // 清空
        deposit.children[0].text = ""
    }
}
```
qml 文件中的代码片段，实现了一个圆角按钮。当按钮被点击时，会调用 C++ 中的 `deposit` 函数，实现存款功能。(user 是一个注册 QML 上下文的 C++ 对象)
```cpp
class Account : public QObject { // 继承自 QObject，纳入 Qt 的对象模型
    Q_OBJECT
    Q_PROPERTY(QString balance READ balance WRITE deposit WRITE withdraw NOTIFY balanceChanged) // 定义属性
    Q_PROPERTY(...)
    ...
signals:
    void balanceChanged();
public:
    QString balance() const;
    void deposit(const QString& amount);
private:
    mpf_class m_balance; // 余额
    ...
};
void Account::deposit(const mpf_class& amount) {
    // 存款
    m_balance += amount;
    // 存储账户信息
    try {
        static_cast<BasicAccount*>(this)->store();
    } catch (const std::runtime_error& e) {
        QMessageBox::warning(nullptr, "存储", e.what());
    }
    // 发送信号
    emit balanceChanged(); // 界面上的余额会随之变化
    // 记录日志
    ...
    QMessageBox::information(nullptr, "存款", "存款成功！");
}
```
Q_PROPERTY 宏定义了一个属性 `balance`，它通过 `READ`、`WRITE`、`NOTIFY` 关键字指定了读取、写入、发出信号的函数。当属性的值发生变化时，会发出一个信号。在 C++ 中，可以通过 `emit` 关键字发出一个信号。在上述代码中，当存款成功时，会发出一个 `balanceChanged` 信号。
此时，界面上的余额会随之变化，实现了动态绑定的效果。
```qml
Text {
    id: balance
    text: "余额：" + user.balance // 界面上的余额
    font.pixelSize: 35
    font.bold: true
    font.family: "Microsoft YaHei"
    anchors.horizontalCenter: parent.horizontalCenter
}
```
# 转账功能
```qml
CustomComboBox {
    id: receiverBox
    model: user.recentTransfers() // 最近的转账记录
    font.pointSize: 20
    onCurrentIndexChanged: {
        receiver.enabled = currentIndex === 0;
    }
    TextField {
        id: receiver
        width: parent.width - 30 // 调整宽度
        height: parent.height
        enabled: parent.currentIndex === 0
        text: enabled ? text : ""
    }
}
```
```cpp
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
    return transfers;
}
```
转账功能基本上与存款功能类似，只是需要增加一个接收方的输入框。在输入框中，可以选择最近的转账记录，也可以手动输入。在 C++ 中，通过 `recentTransfers` 函数获取最近的交易账户，然后在 QML 中显示出来。
```cpp
std::string Log::generate_log() const {
    // 交易时间
    QDateTime time = QDateTime::currentDateTime();
    std::string log =
        (time.toString("yyyy-MM-dd hh:mm:ss") + " ").toStdString();
    // 交易类型
    switch (m_type) {
        case DEPOSIT:
            log += "存款";
            break;
        case WITHDRAW:
            log += "取款";
            break;
        case TRANSFEROUT:
            log += "转账";
            break;
        case TRANSFERIN:
            log += "收款";
            break;
        default:
            break;
    }
    // 交易信息
    log += " 操作人: " + m_id + " 金额: " + m_amount + " 余额: " + m_balance;
    if (m_other != "") {
        log += " 对方: " + m_other;
    }
    log += '\n';
    return log;
}
```
获取最近的转账记录时，需要从交易日志中获取。在 C++ 中，通过 `Log` 类生成交易日志，然后存储到文件中。日志的格式为 "时间 交易类型 操作人 金额 余额 对方"。
# 加密功能
加密功能是一个比较重要的功能，它可以保护用户的隐私信息。在本项目中，维护了一个加密类，封装了`OpenSSL`库的加密算法。在 C++ 中，通过调用加密类的接口，可以实现对用户信息的加密。
```cpp
// 引入 OpenSSL 库
#include <openssl/aes.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>

namespace bms {
class Encryptable;
}
class bms::Encryptable {
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
    ...
};
```