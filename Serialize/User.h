#include "Serializable.h"
#include <QtCore/QDataStream>
#include <QtCore/QFileInfo>
#include <iostream>
#include <ostream>

class User : public bms::Serializable {
public:
    User(const QString& name = "", int age = 0) : m_name(name), m_age(age) {
        QString userFileName = name + ".dat";
        QFile file(userFileName);
        serialize(file);
    }
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
            throw std::runtime_error("Failed to open file for writing");
        }
        ds.setDevice(&file);
        ds << m_name << m_age; 
        file.close();
    }

    Serializable* deserialize(QFile& file) override {
        if (!file.open(QIODevice::ReadOnly)) {
            throw std::runtime_error("Failed to open file for reading");
        }
        QDataStream ds;
        ds.setDevice(&file);
        ds >> m_name >> m_age;
        file.close();
        return this;
    }

    friend std::ostream& operator<<(std::ostream& os, const User& user) {
        os << user.m_name.toStdString() << " " << user.m_age;
        return os;
    }


private:
    QString m_name;
    int m_age;
};
