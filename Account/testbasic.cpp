#include <gtest/gtest.h>
#include <iostream>
#include "Serializable/Serializable.h"
#include "basicAccount.h"
class TestBasic {
public:
    void test() {
        bms::BasicAccount acc("cxk", "123456", "Unkown", "1234567890");
        acc.deposit(1000);
        acc.encrypt();
        std::cout << acc.datafile().fileName().toStdString() << '\n';
        QFile file(acc.datafile());
        file.open(QIODevice::WriteOnly);
        acc.serialize(file);
        file.close();
        acc.display();
        acc.decrypt();
        bms::BasicAccount acc2("fjdsfdj", "114514", "Japan", "1919810");
        acc.transfer(&acc2, 100);
        acc.transfer(&acc2, 2387423);
        acc2.display();
        acc.display();
        // acc2.datafile().remove();
        // acc.datafile().remove();
    }
};

TEST(BasicAccount, test) {
    TestBasic test;
    test.test();
}