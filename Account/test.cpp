#include "account.h"
#include <gtest/gtest.h>

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

// 测试例子
TEST(Account, Constructor) {
    bms::Account a("胡桃", "83457801y5891", "提瓦特 璃月 往生堂", 1234567890);
    a.display();
    EXPECT_EQ(a.name(), "胡桃" );
    bms::Account b;
    b.display();
}

/*
 * 请利用 Google Test 完成 Account 类的测试
 * 自行添加测试
 * 用法可以上网搜索
 */