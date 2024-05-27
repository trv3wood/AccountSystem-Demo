#include "Serializable.h"
using bms::Serializable;

std::string Serializable::mpf_class2str(const mpf_class& number) {
    if (number == 0) {
        return "0";
    }
    mp_exp_t exp;
    std::string s = number.get_str(exp);
    if (exp < 0) {
        s = "0." + std::string(-exp - 1, '0') + s;
    } else if (s.size() - 1 > static_cast<std::string::size_type>(exp) && exp > 0) {
        s.insert(exp, ".");
    } else if (exp == 0) {
        s.insert(0, "0.");
    } else {
        s += std::string(exp - s.size() + 1, '0');
    }
    return s;
}