//
// Created by 王宇 on 2022/1/23.
//

#include "Sphere.h"



bool Sphere::hitTest(const ray& r, double t_min, double t_max, HitRecord& rec)  {
    Cartesian3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Cartesian3 outward_normal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outward_normal);
    get_sphere_uv(outward_normal, rec.u, rec.v);
    rec.material = mat_ptr;

    return true;
}

bool Sphere::boundingBox(double time0, double time1, AABBStructure& output_box)  {
    output_box = AABBStructure(
            center - Cartesian3(radius, radius, radius),
            center + Cartesian3(radius, radius, radius));
    return true;
}