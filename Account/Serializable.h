#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include <string>
#include <gmpxx.h>
namespace bms {
    class Serializable {
    public:
        virtual void serialize(std::string& data) const = 0;
        virtual void deserialize(const std::string& data) = 0;
        virtual ~Serializable() = default;
    protected:
        static std::string mpf_class2str(const mpf_class& number);
    };
}
#endif