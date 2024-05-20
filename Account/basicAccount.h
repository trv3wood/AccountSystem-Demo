#include <algorithm>
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
    std::string m_datafile;    // 数据文件名

public:
    std::string datafile() const { return m_datafile; }
    void transfer(Account* to, const mpf_class& amount) override;
    void serialize(std::string& data) const override;
    void deserialize(const std::string& data) override;

    void store(const std::string& filename);
    void load(const std::string& filename);
    
};
}  // namespace bms