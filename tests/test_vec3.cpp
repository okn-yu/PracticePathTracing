/*
 * Created by okn-yu on 2022/05/02.
 * 関数形式でテストも可能
 * 作成したインスタンスを使い回す場合はこちらのほうが便利
 */

#include <iostream>
#include <gtest/gtest.h>
#include "vec3.hpp"

TEST(Vec3Test, Constructor1) {
    EXPECT_EQ(Vec3().x, 0);
    EXPECT_EQ(Vec3().y, 0);
    EXPECT_EQ(Vec3().z, 0);
}

TEST(Vec3Test, Constructor2) {
    EXPECT_EQ(Vec3(1.0f).x, 1.0);
    EXPECT_EQ(Vec3(1.0f).y, 1.0);
    EXPECT_EQ(Vec3(1.0f).z, 1.0);
}

TEST(Vec3Test, Constructor3) {
    Vec3 v = Vec3(1.0f, 2.0f, 3.0f);
    EXPECT_EQ(v.x, 1.0);
    EXPECT_EQ(v.y, 2.0);
    EXPECT_EQ(v.z, 3.0);
}

TEST(Vec3Test, length) {
    Vec3 v = Vec3(0.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.length(), 5.0f);
}

TEST(Vec3Test, squared_length) {
    Vec3 v = Vec3(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.squared_length(), 14.0f);
}

TEST(Vec3Test, normalize) {
    Vec3 v1 = Vec3(0.0f, 3.0f, 4.0f);
    Vec3 v2 = Vec3(0.0f, 0.6f, 0.8f);

    EXPECT_FLOAT_EQ(v1.normalize().length(), 1);
}

TEST(Vec3Test, reverse) {
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    Vec3 v2 = Vec3(-1.0f, -2.0f, -3.0f);
    EXPECT_EQ(-v1, v2);
}

TEST(Vec3Test, add_equal) {
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    Vec3 v2 = Vec3(-1.0f, -2.0f, -3.0f);
    Vec3 v3 = Vec3(0, 0, 0);
    EXPECT_EQ(v1 += v2, v3);
}

TEST(Vec3Test, sub_equal) {
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    Vec3 v2 = Vec3(-1.0f, -2.0f, -3.0f);
    Vec3 v3 = Vec3(2.0f, 4.0f, 6.0f);
    EXPECT_EQ(v1 -= v2, v3);
}

TEST(Vec3Test, add) {
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    Vec3 v2 = Vec3(-1.0f, -2.0f, -3.0f);
    Vec3 v3 = Vec3(0, 0, 0);
    EXPECT_EQ(v1 + v2, v3);
}

TEST(Vec3Test, sub) {
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    Vec3 v2 = Vec3(-1.0f, -2.0f, -3.0f);
    Vec3 v3 = Vec3(2.0f, 4.0f, 6.0f);
    EXPECT_EQ(v1 - v2, v3);
}

TEST(Vec3Test, mul) {
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    Vec3 v2 = Vec3(-1.0f, -2.0f, -3.0f);
    Vec3 v3 = Vec3(-1.0f, -4.0f, -9.0f);
    EXPECT_EQ(v1 * v2, v3);
}

TEST(Vec3Test, equal) {
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    Vec3 v2 = Vec3(1.0f, 2.0f, 3.0f);
    EXPECT_TRUE(v1 == v2);
}

TEST(Vec3Test, dot) {
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    Vec3 v2 = Vec3(2.0f, 3.0f, 4.0f);
    double t = 20;
    EXPECT_EQ(dot(v1, v2), t);
}

TEST(Vec3Test, cross) {
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    Vec3 v2 = Vec3(0, 1.0f, 2.0f);
    Vec3 v3 = Vec3(1.0f, -2.0f, 1.0f);
    EXPECT_EQ(cross(v1, v2), v3);
}

TEST(Vec3Test, scalar_mul1) {
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    double t = 2;
    Vec3 v2 = Vec3(2.0f, 4.0f, 6.0f);
    EXPECT_EQ(v1 * t, v2);
}

TEST(Vec3Test, scalar_mul2) {
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    double t = 2;
    Vec3 v2 = Vec3(2.0f, 4.0f, 6.0f);
    EXPECT_EQ(t * v1, v2);
}

TEST(Vec3Test, scalar_div1) {
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    double t = 2;
    Vec3 v2 = Vec3(0.5f, 1.0f, 1.5f);
    EXPECT_EQ(v1 / t, v2);
}

TEST(Vec3Test, scalar_div2) {
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    double t = 2;
    Vec3 v2 = Vec3(0.5f, 1.0f, 1.5f);
    EXPECT_EQ(t / v1, v2);
}

TEST(Vec3Test, unit_vec){
    Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
    Vec3 v2 = unit_vec(v1);
    EXPECT_FLOAT_EQ(v2.length(), v2.normalize().length());
}


/*
class TestVec3 : public ::testing::Test {
protected:
    void SetUp() override {
        v0 = new Vec3();
        v1 = new Vec3(1.0f);
        v2 = new Vec3(4.0f, 5.0f, 6.0f);
    }

    void TearDown() override {
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
*/
