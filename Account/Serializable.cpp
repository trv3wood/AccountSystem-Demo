#include "Serializable.h"
#include <sstream>
using bms::Serializable;

std::string Serializable::mpf_class2str(const mpf_class& number, int precision) {
    mp_exp_t exp;
    std::string s = number.get_str(exp);
    
    // 创建一个字符串流来处理格式化
    std::stringstream ss;
    
    // 如果指数是负数，表示小数点在字符串的前面
    if (exp <= 0) {
        ss << "0.";
        for (int i = 0; i < -exp; ++i) {
            ss << "0";
        }
        ss << s;
    } else {
        // 把字符串的前exp个字符作为整数部分
        if (s.size() > static_cast<size_t>(exp)) {
            ss << s.substr(0, exp) << "." << s.substr(exp);
        } else {
            ss << s;
            for (int i = s.size(); i < exp; ++i) {
                ss << "0";
            }
            ss << ".0";
        }
    }
    
    // 设置精度
    std::string result = ss.str();
    size_t dot_pos = result.find('.');
    if (dot_pos != std::string::npos) {
        // 如果小数点后的位数超过精度，截断
        result = result.substr(0, dot_pos + precision + 1);
        // 不足的补0
        while (static_cast<int>(result.size() - dot_pos) < precision + 1) {
            result += "0";
        }
    }
    if (result.back() == '.') {
        result.pop_back();
    }
    return result;
}

QString Serializable::mpf2str(const mpf_class& number) {
    mp_exp_t exp;
    std::string s = number.get_str(exp);
    QString result = QString::fromStdString(s);
    // xxe+yy
    if (result.isEmpty()) {
        return "0";
    }
    if (exp != 0) {
        result += "e" + QString::number(exp);
    }
    if (exp == 0) {
        result = "0." + result;
    }
    return result;
}
