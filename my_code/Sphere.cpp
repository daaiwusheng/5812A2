//
// Created by 王宇 on 2022/1/23.
//

#include "Sphere.h"


Sphere::Sphere() {

}
Sphere::Sphere(Cartesian3 _center, double r, shared_ptr<Material> _material)
        : center(_center), radius(r), material(_material) {

}

bool Sphere::hitTest(const Ray& ray, double t_min, double t_max, HitRecord& rec)  {
    Cartesian3 oc = ray.origin() - center;
    auto a = ray.direction().length_squared();
    auto half_b = dot(oc, ray.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // here is important, as we want to get the closest point.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        //if the first root can not satisfy the range.
        //we need consider the second root.
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = ray.at(rec.t);
    Cartesian3 outward_normal = (rec.p - center) / radius;
    rec.setFaceNormal(ray, outward_normal);
    getSphere_uv(outward_normal, rec.u, rec.v);
    rec.material = material;

    return true;
}

bool Sphere::boundingBox(double time0, double time1, AABBStructure& outputBox)  {
    outputBox = AABBStructure(
            center - Cartesian3(radius, radius, radius),
            center + Cartesian3(radius, radius, radius));
    return true;
}

void Sphere::getSphere_uv(const Cartesian3 &p, double &u, double &v) {

    auto theta = acos(-p.y);
    auto phi = atan2(-p.z, p.x) + pi;

    u = phi / (2*pi);
    v = theta / pi;
}



