#include <gmp.h>
#include <gmpxx.h>
#include <gtest/gtest.h>

#include <QString>
#include <iostream>
#include <ostream>
#include <string>

#include "Serializable.h"

class TestSerializable : public bms::Serializable {
public:
    TestSerializable() = default;
    TestSerializable(int a, double b, QString c, long long d, float e, bool f)
        : a(a), b(b), c(std::move(c)), d(d), e(e), f(f) {
        QFile file("test.dat");
        serialize(file);
    }
    int a;
    double b;
    QString c;
    long long d;
    float e;
    bool f;

    void serialize(QFile& file) const override {
        basicSerialize(file);
    }

    void deserialize(QFile& file) override {
        basicDeserialize(file);
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const TestSerializable& ts) {
        os << ts.a << ' ' << ts.b << ' ' << ts.c.toStdString() << ' ' << ts.d
           << ' ' << ts.e << ' ' << (ts.f ? "true" : "false");
        return os;
    }

private:
    SERIALIZE(a, b, c, d, e, f)
};

class TestComplexType : public bms::Serializable {
public: 
    mpf_class a;
    mpz_class b;
    std::string c;
    void serialize(QFile& file) const override {
        mp_exp_t exp;
        std::string aStr = a.get_str(exp);
        aStr.insert(exp, ".");
        std::string bStr = b.get_str(exp);
        std::cout << aStr << ' ' << bStr << ' ' << c << std::endl;
        if (!file.open(QIODevice::WriteOnly)) {
            throw std::runtime_error("Cannot open file");
        }
        QDataStream ds(&file);
        ds << QString::fromStdString(aStr) << QString::fromStdString(bStr) << QString::fromStdString(c);
        file.close();
    }

    void deserialize(QFile& file) override {
        if (!file.open(QIODevice::ReadOnly)) {
            throw std::runtime_error("Cannot open file");
        }
        QDataStream ds(&file);
        QString aStr, bStr, cStr;
        ds >> aStr >> bStr >> cStr;
        a = mpf_class(aStr.toStdString());
        b = mpz_class(bStr.toStdString());
        c = cStr.toStdString();
        file.close();
    }
private:
    bms::Serializable* basicDeserialize(QFile& file) override {
        return nullptr;
    }
    void basicSerialize(QFile& file) const override {}
};

TEST(Serializable, Test) {
    TestSerializable ts(1, 2.0, "3", 4, 5.0, true);
    std::cout << ts << std::endl;
    TestSerializable ts2;
    QFile file("test.dat");
    ts2.deserialize(file);
    std::cout << ts2 << std::endl;
    ASSERT_EQ(ts.a, ts2.a);
    ASSERT_EQ(ts.b, ts2.b);
    ASSERT_EQ(ts.c, ts2.c);
    ASSERT_EQ(ts.d, ts2.d);
    ASSERT_EQ(ts.e, ts2.e);
    ASSERT_EQ(ts.f, ts2.f);
}

TEST(Serializable, ComplexType) {
    TestComplexType tct;
    tct.a = mpf_class("1.7245936295926593265965829638925893");
    tct.b = mpz_class("579834758439545748");
    tct.c = "Hello, World!";
    QFile file("test.dat");
    tct.serialize(file);
    TestComplexType tct2;
    tct2.deserialize(file);
    ASSERT_EQ(tct.a.get_d(), tct2.a.get_d());
    ASSERT_EQ(tct.b.get_d(), tct2.b.get_d());
    ASSERT_EQ(tct.c, tct2.c);
}