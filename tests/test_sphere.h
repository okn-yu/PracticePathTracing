//
// Created by okn-yu on 2022/05/05.
//

#include <gtest/gtest.h>
#include "hittable.h"
#include "ray.h"
#include "sphere.h"

TEST(SphereTest, Hittable) {
    Sphere s(Point3(0.0f, 0.0f, 0.0f), 1.0f);
    Ray ray(Vec3(0, 0, -3), Vec3(0, 0, 1));
    HitRecord hit_record;
    bool is_hittable = s.hit(ray, hit_record);

    EXPECT_EQ(is_hittable, true);
    EXPECT_EQ(hit_record.hit_pos, (0.0f, 0.0f, -1.0f));
}


