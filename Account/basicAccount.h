#include "Encryptable/Encryptable.h"
#include "Serializable/Serializable.h"
#include "account.h"

namespace bms {
class BasicAccount : public Account, public Serializable {
public:
    BasicAccount() = default;
    BasicAccount(QString name, QString passwd, QString location, QString id);

private:
    static const unsigned transferRestriction;
    virtual QString predecrypt(const QString& a) = 0;

public:
    void transfer(Account* to, const mpf_class& amount) override;
    void serialize(QFile& file) const override;
    void deserialize(QFile& file) override;
    void deposit(const mpf_class& amount) override;
    void setPasswd(const QString& passwd) override;
    void encrypt() override;
    void decrypt() override;

    SERIALIZE(m_name, m_passwd, m_location, m_id, m_cardNumber); // 只能包括基本类型
};
}  // namespace bms