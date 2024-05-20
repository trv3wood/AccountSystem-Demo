#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include <iostream>
#include <sstream>
#include <QtCore/QDataStream>
#include <QtCore/QFile>
namespace bms {
    class Serializable {
    protected:
        virtual void basicSerialize(QDataStream& ds, QFile& file) const {};
        virtual void basicDeserialize(QDataStream& ds, QFile& file) {};
    public:
        virtual void serialize(std::string& data) const = 0;
        virtual void deserialize(const std::string& data) = 0;
        virtual ~Serializable() = default;
    };
}
#define SERIALIZE(...) \
    void basicSerialize(QDataStream& ds, QFile& file) const override { \
        ds.setDevice(&file); \
        ds.setVersion(QDataStream::Qt_5_15); \
        serializeImpl(ds, __VA_ARGS__); \
    } \
    void basicDeserialize(QDataStream& ids, QFile& file) override { \
        ids.setDevice(&file); \
        ids.setVersion(QDataStream::Qt_5_15); \
        deserializeImpl(ids, __VA_ARGS__); \
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