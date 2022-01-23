//
// Created by 王宇 on 2022/1/23.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_SPHERE_H
#define RAYTRACERENDERWINDOWRELEASE_SPHERE_H


#include "hittable.h"
#include "../Cartesian3.h"
#include "Material.h"
#include "utility.h"

class Sphere : public hittable {
public:
    Sphere() {}
    Sphere(Cartesian3 cen, double r, shared_ptr<Material> m)
            : center(cen), radius(r), mat_ptr(m) {};

    virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) override;
    virtual bool bounding_box(double time0, double time1, AABBStructure& output_box) override;

public:
    Cartesian3 center;
    double radius;
    shared_ptr<Material> mat_ptr;


private:
    static void get_sphere_uv(const Cartesian3& p, double& u, double& v) {
        // p: a given point on the Sphere of radius one, centered at the origin.
        // u: returned value [0,1] of angle around the Y axis from X=-1.
        // v: returned value [0,1] of angle from Y=-1 to Y=+1.
        //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
        //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
        //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

        auto theta = acos(-p.y);
        auto phi = atan2(-p.z, p.x) + pi;

        u = phi / (2*pi);
        v = theta / pi;
    }

};


#endif //RAYTRACERENDERWINDOWRELEASE_SPHERE_H
