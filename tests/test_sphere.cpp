/*
 * Created by okn-yu on 2022/05/05.
 */

#include <gtest/gtest.h>
#include "object/hit.hpp"
#include "ray.hpp"
#include "object/sphere.hpp"

TEST(SphereTest, RayHit) {
    Sphere sphere(Vec3(0.0f, 0.0f, 0.0f), 1.0f);
    Ray ray(Vec3(0, 0, -3), Vec3(0, 0, 1));
    HitRecord hit_record;
    bool is_hittable = sphere.is_hittable(ray, hit_record);

    EXPECT_EQ(is_hittable, true);
    EXPECT_EQ(hit_record.t, 2);
    EXPECT_EQ(hit_record.hit_pos, Vec3(0.0f, 0.0f, -1.0f));
}

TEST(SphereTest, RayNotHit) {
    Sphere sphere(Vec3(0.0f, 0.0f, 0.0f), 1.0f);
    Ray ray(Vec3(4, 0, 0), Vec3(0, 0, 1));
    HitRecord hit_record;
    bool is_hittable = sphere.is_hittable(ray, hit_record);

    EXPECT_EQ(is_hittable, false);
    //EXPECT_EQ(hit_record.t, 2);
    //EXPECT_EQ(hit_record.hit_pos, Vec3(0.0f, 0.0f, -1.0f));
}

TEST(SphereTest, RayTangent) {
    Sphere sphere(Vec3(0.0f, 0.0f, 0.0f), 1.0f);
    Ray ray(Vec3(0, 1, -1), Vec3(0, 0, 1));
    HitRecord hit_record;
    bool is_hittable = sphere.is_hittable(ray, hit_record);

    EXPECT_EQ(is_hittable, true);
    EXPECT_EQ(hit_record.t, 1);
    EXPECT_EQ(hit_record.hit_pos, Vec3(0.0f, 1.0f, 0.0f));
}


