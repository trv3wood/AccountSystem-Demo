## Account 类
Account 类用于表示一个账户，包含账户的基本信息，如账户名、密码、余额等。
### 方法
```cpp
    Account() {}
    /// @brief 构造函数
    Account(const QString& name, const QString& passwd, const QString& location, const QString& id);

    /// 用户名、密码、地点、身份证号码等
    QString name() const;
    QString passwd() const;
    QString location() const;
    QString id() const;
    mpf_class balance() const;
    mpf_class interestRate() const;
    QString cardNumber() const;

    /// @brief 设置账户名、密码、地点、身份证号码等
    void setName(const QString& name);
    void setPasswd(const QString& passwd);
    void setLocation(const QString& location);
    void setId(const QString& id);
    void setInterestRate(double rate);

    /// @brief 设置二类卡用户（复写）的账户余额,信息存储、读取，以及存款和密码设置（密码输入正确才能进行操作）
    void transfer(Account* to, const mpf_class& amount) override;
    void serialize(QFile& file) const override;
    void deserialize(QFile& file) override;
    void deposit(const mpf_class& amount) override;
    void setPasswd(const QString& passwd) override;

    /// @brief 设置账户余额
    virtual void transfer(Account& to, mpf_class amount);

    /// @brief 存款
    void deposit(mpf_class amount);

    /// @brief 将mpf_class2str类型数字转化为字符串
    QString mpf_class2str(const mpf_class& number);

    /// @brief 随机生成16位卡号
    QString generateCardNumber();

    /// @brief将数据转化为哈希值
    QString hashSHA256(const QString& str, int lenMultiplier);

    void display() const;
```
