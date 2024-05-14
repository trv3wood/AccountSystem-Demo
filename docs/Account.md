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

    /// @brief 设置账户余额
    virtual void transfer(Account& to, mpf_class amount);

    /// @brief 存款
    void deposit(mpf_class amount);

    void display() const;
```
