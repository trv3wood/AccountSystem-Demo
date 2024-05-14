## Serializable 类
Serializable 类是一个抽象类，用于定义可序列化的对象的接口。Serializable 类的子类可以通过实现 `serialize` 和 `deserialize` 方法来实现对象的序列化和反序列化。
### 方法
```cpp
    virtual void serialize(QFile& file) const = 0;
    virtual Serializable* deserialize(QFile& file) = 0;
```
#### `serialize` 方法
`serialize` 方法用于将对象序列化到文件中。`file` 参数是一个 QFile 对象，用于指定要写入的文件。
#### `deserialize` 方法
`deserialize` 方法用于从文件中反序列化对象。`file` 参数是一个 QFile 对象，用于指定要读取的文件。`deserialize` 方法返回一个指向新创建的对象的指针。

### 序列化宏 `SERIALIZE`
`SERIALIZE` 宏用于定义一个可序列化的类。`SERIALIZE` 宏接受一个类名作为参数，该类名必须是 `Serializable` 类的子类。`SERIALIZE` 宏会自动为该类添加 `serialize` 和 `deserialize` 方法。
#### 示例
```cpp
class Account : public Serializable {
private:
    QString name_;
    QString passwd_;
    QString location_;
    QString id_;
    SERIALIZE(name_, passwd_, location_, id_)
    // ...
};
```
#### 具体宏定义
```cpp
#define SERIALIZE(...) \
    void serialize(QFile& file) const override { \
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
    Serializable* deserialize(QFile& file) override { \
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
```