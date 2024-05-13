#include "account.h"
#include <gtest/gtest.h>

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

// 测试例子
TEST(Account, Constructor) {
    bms::Account a("胡桃", "123456", "璃月 往生堂", "1234567890");
    EXPECT_EQ(a.name(), "胡桃" );
    bms::Account b;
    b.display();
    EXPECT_EQ(b.name(), "");
    b.setName("胡桃");
    b.display();
}


/*
 * 请利用 Google Test 完成 Account 类的测试
 * 自行添加测试
 * 用法可以上网搜索
 */