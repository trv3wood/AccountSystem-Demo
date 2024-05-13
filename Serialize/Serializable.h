#ifndef SERIALIZE_SERIALIZABLE_H
#define SERIALIZE_SERIALIZABLE_H
#include <iostream>
#include <sstream>
#include <QtCore/QDataStream>
#include <QtCore/QFile>
namespace bms {
    class Serializable {
    public:
        virtual void serialize(QFile& file) const = 0;
        virtual Serializable* deserialize(QFile& file) = 0;
    };
}
/*
#define SERIALIZE(...) \
    void serialize() const override { \
        QDataStream ds; \
        if (!file.open(QIODevice::WriteOnly)) { \ 
            std::cerr << "Failed to open file for writing" << '\n'; \
        } \
        ds.setDevice(&file); \
        ds << name << age; \
        file.close();\
    } \
    Serializable* deserialize(const QDataStream& s) override { \
        QDataStream ids(s); \
        deserializeImpl(ids, __VA_ARGS__); \
    } \
private: \
    template<typename T> \
    void serializeImpl(QDataStream& ods, const T& t) const { \
        ods << t << " "; \
    } \
    template<typename T, typename... Args> \
    void serializeImpl(QDataStream& ods, const T& t, const Args&... args) const { \
        ods << t << " "; \
        serializeImpl(ods, args...); \
    } \
    template<typename T> \
    void deserializeImpl(QDataStream& ids, T& t) { \
        ids >> t; \
    } \
    template<typename T, typename... Args> \
    void deserializeImpl(QDataStream& ids, T& t, Args&... args) { \
        ids >> t; \
        deserializeImpl(ids, args...); \
    }
*/
#endif // SERIALIZE_SERIALIZABLE_H