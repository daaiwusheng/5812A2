//
// Created by 王宇 on 2022/1/23.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_SPHERE_H
#define RAYTRACERENDERWINDOWRELEASE_SPHERE_H


#include "HittableObject.h"
#include "../Cartesian3.h"
#include "Material.h"
#include "utility.h"

//the sphere object is also a subclass of HittableObject,
//as we need to test if a ray hits it in our scene.
class Sphere : public HittableObject {
public:
    Sphere();
    Sphere(Cartesian3 _center, double r, shared_ptr<Material> _material);;

    virtual bool hitTest(
            const Ray& ray, double t_min, double t_max, HitRecord& rec) override;
    virtual bool boundingBox(double time0, double time1, AABBStructure& outputBox) override;

public:
    Cartesian3 center;
    double radius;
    shared_ptr<Material> material;


private:
    static void get_sphere_uv(const Cartesian3& p, double& u, double& v) {

        auto theta = acos(-p.y);
        auto phi = atan2(-p.z, p.x) + pi;

        u = phi / (2*pi);
        v = theta / pi;
    }

};


#endif //RAYTRACERENDERWINDOWRELEASE_SPHERE_H
