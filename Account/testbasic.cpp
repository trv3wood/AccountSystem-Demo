#include <gtest/gtest.h>
#include "basicAccount.h"
class TestBasic {
public:
    void test() {
        bms::BasicAccount acc("cxk", "123456", "Unkown", "1234567890");
        QFile file(acc.datafile());
        acc.deposit(1000);
        acc.serialize(file);
        acc.display();
        bms::BasicAccount acc2("fjdsfdj", "114514", "Japan", "1919810");
        acc.transfer(&acc2, 100);
        acc.transfer(&acc2, 2387423);
        acc2.display();
        acc2.datafile().remove();
        acc.datafile().remove();
    }
};

TEST(BasicAccount, test) {
    TestBasic test;
    test.test();
}