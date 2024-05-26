#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include <string>
namespace bms {
    class Serializable {
    public:
        virtual void serialize(std::string& data) const = 0;
        virtual void deserialize(const std::string& data) = 0;
        virtual ~Serializable() = default;
    };
}
#endif