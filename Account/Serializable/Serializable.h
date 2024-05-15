#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include <iostream>
#include <sstream>
#include <QtCore/QDataStream>
#include <QtCore/QFile>
namespace bms {
    class Serializable {
    public:
        virtual void basicSerialize(QFile& file) const = 0;
        virtual Serializable* basicDeserialize(QFile& file) = 0;
        virtual void serialize(QFile& file) const = 0;
        virtual Serializable* deserialize(QFile& file) = 0;
        virtual ~Serializable() = default;
    };
}
#define SERIALIZE(...) \
    void basicSerialize(QFile& file) const override { \
        QDataStream ds; \
        if (!file.open(QIODevice::WriteOnly)) { \
            std::cerr << "Cannot open file for writing" << std::endl; \
            return; \
        } \
        ds.setDevice(&file); \
        ds.setVersion(QDataStream::Qt_5_15); \
        serializeImpl(ds, __VA_ARGS__); \
        file.close();\
    } \
    Serializable* basicDeserialize(QFile& file) override { \
        QDataStream ids; \
        if (!file.open(QIODevice::ReadOnly)) { \
            throw std::runtime_error("Failed to open file for reading"); \
        } \
        ids.setDevice(&file); \
        ids.setVersion(QDataStream::Qt_5_15); \
        deserializeImpl(ids, __VA_ARGS__); \
        file.close(); \
        return this; \
    } \
private: \
    template<typename T> \
    void serializeImpl(QDataStream& ods, const T& t) const { \
        ods << t; \
    } \
    template<typename T, typename... Args> \
    void serializeImpl(QDataStream& ods, const T& t, const Args&... args) const { \
        ods << t; \
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
#endif // SERIALIZABLE_H