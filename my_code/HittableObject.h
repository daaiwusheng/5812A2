//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_HITTABLEOBJECT_H
#define RAYTRACERENDERWINDOWRELEASE_HITTABLEOBJECT_H

#include "ray.h"
#include "headers.h"
#include "Material.h"
#include "AABBStructure.h"
#include "../Cartesian3.h"

struct HitRecord {
    Cartesian3 p;
    Cartesian3 normal;
    shared_ptr<Material> material;
    double t;
    double u;
    double v;
    bool frontFace;

    inline void setFaceNormal(const ray& r, const Cartesian3& outwardNormal) {
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -1 * outwardNormal;
    }
};

class HittableObject {
public:
    virtual bool hitTest(const ray& r, double t_min, double t_max, HitRecord& rec) = 0;
    virtual bool boundingBox(double time0, double time1, AABBStructure& outputBox) = 0;
};

class translate : public HittableObject {
public:
    translate(shared_ptr<HittableObject> p, const Cartesian3& displacement)
            : ptr(p), offset(displacement) {}

    virtual bool hitTest(
            const ray& r, double t_min, double t_max, HitRecord& rec) override;

    virtual bool boundingBox(double time0, double time1, AABBStructure& outputBox) override;

public:
    shared_ptr<HittableObject> ptr;
    Cartesian3 offset;
};


class rotate_y : public HittableObject {
public:
    rotate_y(shared_ptr<HittableObject> p, double angle);

    virtual bool hitTest(
            const ray& r, double t_min, double t_max, HitRecord& rec) override;

    virtual bool boundingBox(double time0, double time1, AABBStructure& outputBox) override;

public:
    shared_ptr<HittableObject> ptr;
    double sin_theta;
    double cos_theta;
    bool hasbox;
    AABBStructure bbox;
};


class flip_face : public HittableObject {
public:
    flip_face(shared_ptr<HittableObject> p) : ptr(p) {}

    virtual bool hitTest(
            const ray& r, double t_min, double t_max, HitRecord& rec)  override;

    virtual bool boundingBox(double time0, double time1, AABBStructure& outputBox) override;

public:
    shared_ptr<HittableObject> ptr;
};


#endif //RAYTRACERENDERWINDOWRELEASE_HITTABLEOBJECT_H
