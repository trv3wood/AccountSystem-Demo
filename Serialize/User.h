#include "Serializable.h"
#include <QtCore/QDataStream>
#include <QtCore/QFileInfo>
#include <iostream>
#include <ostream>

class User : public bms::Serializable {
public:
    User(const QString& name = "", int age = 0) : name(name), age(age) {}
    User(QFile& file) {
        deserialize(file);
    }
    User(const QFileInfo& fileInfo) {
        QFile file(fileInfo.filePath());
        deserialize(file);
    }

    void serialize(QFile& file) const override {
        QDataStream ds;
        if (!file.open(QIODevice::WriteOnly)) {
            std::cerr << "Failed to open file for writing" << '\n';
        }
        ds.setDevice(&file);
        ds << name << age;
        file.close();
    }

    Serializable* deserialize(QFile& file) override {
        if (!file.open(QIODevice::ReadOnly)) {
            std::cerr << "Failed to open file for reading" << '\n';
        }
        QDataStream ds;
        ds.setDevice(&file);
        ds >> name >> age;
        file.close();
        return this;
    }

    friend std::ostream& operator<<(std::ostream& os, const User& user) {
        os << user.name.toStdString() << " " << user.age;
        return os;
    }


private:
    QString name;
    int age;
};
