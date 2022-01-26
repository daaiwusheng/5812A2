//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_AARECT_H
#define RAYTRACERENDERWINDOWRELEASE_AARECT_H

#include "HittableObject.h"

//in this file, we define three axis-aligned rectangle classes.
//they are all subclass of HittableObject.

class xy_rectangle : public HittableObject {
public:
    xy_rectangle();

    xy_rectangle(double _x0, double _x1, double _y0, double _y1, double _z,
                 shared_ptr<Material> _material);;

    virtual bool hitTest(const Ray& r, double t_min, double t_max, HitRecord& rec) override;

    virtual bool boundingBox(double time0, double time1, AABBStructure& output_box) override;

public:
    shared_ptr<Material> material;
    double x0, x1, y0, y1, z;
};


class xz_rectangle : public HittableObject {
public:
    xz_rectangle();

    xz_rectangle(double _x0, double _x1, double _z0, double _z1, double _y,
                 shared_ptr<Material> _material);;

    virtual bool hitTest(const Ray& r, double t_min, double t_max, HitRecord& rec) override;

    virtual bool boundingBox(double time0, double time1, AABBStructure& output_box) override;

    virtual double pdf_value(const Cartesian3& origin, const Cartesian3& v) override;

    virtual Cartesian3 random(const Cartesian3& origin) override;

public:
    shared_ptr<Material> material;
    double x0, x1, z0, z1, y;
};



class yz_rectangle : public HittableObject {
public:
    yz_rectangle();

    yz_rectangle(double _y0, double _y1, double _z0, double _z1, double _x,
                 shared_ptr<Material> _material);;

    virtual bool hitTest(const Ray& r, double t_min, double t_max, HitRecord& rec) override;

    virtual bool boundingBox(double time0, double time1, AABBStructure& output_box) override;

public:
    shared_ptr<Material> material;
    double y0, y1, z0, z1, x;

};

#endif //RAYTRACERENDERWINDOWRELEASE_AARECT_H
