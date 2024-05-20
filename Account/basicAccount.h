#include <string>
#include "Encryptable/Encryptable.h"
#include "Serializable/Serializable.h"
#include "account.h"

namespace bms {
class BasicAccount : public Account, public Serializable, public Encryptable {
public:
    BasicAccount() = default;
    BasicAccount(const std::string& name, const std::string& passwd,
                 const std::string& location, const std::string& id);

private:
    static const unsigned transferRestriction;

public:
    std::string m_datafile;    // 数据文件名
    QFile datafile() const { return QFile(QString::fromStdString(m_datafile)); }
    void transfer(Account* to, const mpf_class& amount) override;
    void serialize(QFile& file) const override;
    void deserialize(QFile& file) override;
    void setPasswd(const std::string& passwd) override;
    void encrypt() override;
    void decrypt() override;

    void store();
    void load(QFile& file);
};
}  // namespace bms