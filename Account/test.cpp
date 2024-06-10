#include "basicAccount.h"
#include <gtest/gtest.h>
#include <cstdlib>

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

// 测试例子
TEST(basicAccount, Constructor) {
    bms::BasicAccount a("李田所", "1919810", "下北泽", "114514");
    a.store(a.datafile());
    a.display();
    bms::BasicAccount b;
    b.load(a.datafile());
    EXPECT_EQ(a.id(), b.id());
    b.transfer(&a, 100);
    b.display();
    b.deposit("1000");
    b.transfer(&a, 100);
    a.display();
    b.display();
    system("rm *.dat");
}

TEST(basicAccount, load) {
    bms::BasicAccount user("18823231622", "@Ricky4881");
    user.store(user.datafile());
    EXPECT_EQ(user.datafile(), "aa9656f7.dat");
    user.load(user.datafile());
    user.display();
    system("rm *.dat");
}
/*
 * 请利用 Google Test 完成 Account 类的测试
 * 自行添加测试
 * 用法可以上网搜索
 */
