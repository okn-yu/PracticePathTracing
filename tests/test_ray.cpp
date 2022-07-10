/*
 * Created by okn-yu on 2022/05/04.
 */

#include <gtest/gtest.h>
#include "core/ray.hpp"

TEST(RayTest, Constructor) {
    Ray r(Vec3(1, 2, 3), Vec3(0, 1, 2));
    EXPECT_EQ(r(0).x(), 1);
    EXPECT_EQ(r(0).y(), 2);
    EXPECT_EQ(r(0).z(), 3);

    EXPECT_EQ(r(10).x(), 1.0f);
    EXPECT_EQ(r(10).y(), 12.0f);
    EXPECT_EQ(r(10).z(), 23.0f);
}

