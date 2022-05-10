//
// Created by okn-yu on 2022/05/02.
//

#include <gtest/gtest.h>
#include <iostream>
#include "../include/vec3.h"


class TestVec3 : public ::testing::Test {
protected:
    virtual void SetUp() {
        v0 = new Vec3(); //引数なしコンストラクタに（）は不要
        v1 = new Vec3(1.0f);
        v2 = new Vec3(4.0f, 5.0f, 6.0f);
    }

    virtual void TearDown() {
        std::cout << "TEST_F finished." << std::endl;
    }
    //組み込み型以外はポインタ型で宣言しないとエラーとなる
    Vec3 *v0;
    Vec3 *v1;
    Vec3 *v2;
};

TEST_F(TestVec3, Constructor) {
    EXPECT_EQ(v0->x, 0.0f);
    EXPECT_EQ(v0->y, 0.0f);
    EXPECT_EQ(v0->z, 0.0f);

    EXPECT_EQ(v1->x, 1.0f);
    EXPECT_EQ(v1->y, 1.0f);
    EXPECT_EQ(v1->z, 1.0f);

    EXPECT_EQ(v2->x, 4.0f);
    EXPECT_EQ(v2->y, 5.0f);
    EXPECT_EQ(v2->z, 6.0f);
}

TEST_F(TestVec3, Operators) {
    EXPECT_EQ((*v1 + *v2).x, 5.0f);
    EXPECT_EQ((*v1 + *v2).y, 6.0f);
    EXPECT_EQ((*v1 + *v2).z, 7.0f);

}
