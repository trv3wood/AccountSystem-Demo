#include "Serializable.h"
#include <QtCore/QDataStream>
#include <QtCore/QFileInfo>
#include <iostream>
#include <ostream>

class User : public bms::Serializable {
public:
    User(const QString& name = "", int age = 0, double magicNum = 0.571032) :
    m_name(name), m_dataFilePath(name + ".dat"), m_magicNumber(magicNum), m_age(age) {
        QFile file(m_dataFilePath);
        serialize(file);
    }
    User(QFile& file) {
        deserialize(file);
    }
    User(const QFileInfo& fileInfo) {
        QFile file(fileInfo.filePath());
        deserialize(file);
    }
    User(const QString& dataFilePath) : m_dataFilePath(dataFilePath) {
        QFile file(dataFilePath);
        deserialize(file);
    }

    friend std::ostream& operator<<(std::ostream& os, const User& user) {
        os << user.m_name.toStdString() << " " << user.m_dataFilePath.toStdString() << ' ' << user.m_magicNumber
        << " " << user.m_age;
        return os;
    }
    SERIALIZE(m_name, m_dataFilePath, m_magicNumber, m_age)

private:
    QString m_name;
    QString m_dataFilePath;
    double m_magicNumber;
    int m_age;
};
