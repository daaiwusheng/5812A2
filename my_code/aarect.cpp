//
// Created by 王宇 on 2022/1/19.
//

#include "aarect.h"
#include "../Cartesian3.h"

//in this file, I only comments xz_rectangle, as they other two are the same.

xz_rectangle::xz_rectangle() {

}

xz_rectangle::xz_rectangle(double _x0, double _x1, double _z0, double _z1, double _y, shared_ptr<Material> _material)
        : x0(_x0), x1(_x1), z0(_z0), z1(_z1), y(_y), material(_material) {

}

bool xz_rectangle::hit(const ray& r, double t_min, double t_max, HitRecord& rec) {
    //solving the equation is easy. but we need keep an eye on that
    // t should be between t_min and t_max.
    auto t = (y - r.origin().y) / r.direction().y;
    if (t < t_min || t > t_max)
        return false;
    //if t is valid, then we can calculate the point where the ray intersect with the planes
    auto x = r.origin().x + t*r.direction().x;
    auto z = r.origin().z + t*r.direction().z;
    if (x < x0 || x > x1 || z < z0 || z > z1)
        return false;
    //store these data in hit record. we will use them to calculate the ray tracer.
    rec.u = (x-x0)/(x1-x0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    auto outwardNormal = Cartesian3(0, 1, 0);
    rec.setFaceNormal(r, outwardNormal);
    rec.material = material;
    rec.p = r.at(t);
    return true;
}


bool xz_rectangle::bounding_box(double time0, double time1, AABBStructure &output_box) {
    // The bounding box can not have zero width in each dimension, so add the Y
    // dimension a small number.
    output_box = AABBStructure(Cartesian3(x0, y - 0.0001, z0), Cartesian3(x1, y + 0.0001, z1));
    return true;
}

xy_rectangle::xy_rectangle() {

}

xy_rectangle::xy_rectangle(double _x0, double _x1, double _y0, double _y1, double _z, shared_ptr<Material> _material)
        : x0(_x0), x1(_x1), y0(_y0), y1(_y1), z(_z), material(_material) {

}

bool xy_rectangle::hit(const ray& r, double t_min, double t_max, HitRecord& rec) {
    auto t = (z - r.origin().z) / r.direction().z;
    if (t < t_min || t > t_max)
        return false;
    auto x = r.origin().x + t*r.direction().x;
    auto y = r.origin().y + t*r.direction().y;
    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;
    rec.u = (x-x0)/(x1-x0);
    rec.v = (y-y0)/(y1-y0);
    rec.t = t;
    auto outwardNormal = Cartesian3(0, 0, 1);
    rec.setFaceNormal(r, outwardNormal);
    rec.material = material;
    rec.p = r.at(t);
    return true;
}

bool xy_rectangle::bounding_box(double time0, double time1, AABBStructure &output_box) {
    output_box = AABBStructure(Cartesian3(x0, y0, z - 0.0001), Cartesian3(x1, y1, z + 0.0001));
    return true;
}

yz_rectangle::yz_rectangle() {

}

yz_rectangle::yz_rectangle(double _y0, double _y1, double _z0, double _z1, double _x, shared_ptr<Material> _material)
        : y0(_y0), y1(_y1), z0(_z0), z1(_z1), x(_x), material(_material) {

}

bool yz_rectangle::hit(const ray& r, double t_min, double t_max, HitRecord& rec) {
    auto t = (x - r.origin().x) / r.direction().x;
    if (t < t_min || t > t_max)
        return false;
    auto y = r.origin().y + t*r.direction().y;
    auto z = r.origin().z + t*r.direction().z;
    if (y < y0 || y > y1 || z < z0 || z > z1)
        return false;
    rec.u = (y-y0)/(y1-y0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    auto outwardNormal = Cartesian3(1, 0, 0);
    rec.setFaceNormal(r, outwardNormal);
    rec.material = material;
    rec.p = r.at(t);
    return true;
}

bool yz_rectangle::bounding_box(double time0, double time1, AABBStructure &output_box) {
    output_box = AABBStructure(Cartesian3(x - 0.0001, y0, z0), Cartesian3(x + 0.0001, y1, z1));
    return true;
}


