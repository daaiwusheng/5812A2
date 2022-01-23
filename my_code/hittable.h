//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_HITTABLE_H
#define RAYTRACERENDERWINDOWRELEASE_HITTABLE_H

#include "ray.h"
#include "headers.h"
#include "Material.h"
#include "AABBStructure.h"
#include "../Cartesian3.h"

struct hit_record {
    Cartesian3 p;
    Cartesian3 normal;
    shared_ptr<Material> mat_ptr;
    double t;
    double u;
    double v;
    bool front_face;

    inline void set_face_normal(const ray& r, const Cartesian3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-1*outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) = 0;
    virtual bool bounding_box(double time0, double time1, AABBStructure& output_box) = 0;
};

class translate : public hittable {
public:
    translate(shared_ptr<hittable> p, const Cartesian3& displacement)
            : ptr(p), offset(displacement) {}

    virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) override;

    virtual bool bounding_box(double time0, double time1, AABBStructure& output_box) override;

public:
    shared_ptr<hittable> ptr;
    Cartesian3 offset;
};


class rotate_y : public hittable {
public:
    rotate_y(shared_ptr<hittable> p, double angle);

    virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) override;

    virtual bool bounding_box(double time0, double time1, AABBStructure& output_box) override;

public:
    shared_ptr<hittable> ptr;
    double sin_theta;
    double cos_theta;
    bool hasbox;
    AABBStructure bbox;
};


class flip_face : public hittable {
public:
    flip_face(shared_ptr<hittable> p) : ptr(p) {}

    virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec)  override;

    virtual bool bounding_box(double time0, double time1, AABBStructure& output_box) override;

public:
    shared_ptr<hittable> ptr;
};


#endif //RAYTRACERENDERWINDOWRELEASE_HITTABLE_H
