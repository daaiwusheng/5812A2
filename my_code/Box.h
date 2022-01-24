//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_BOX_H
#define RAYTRACERENDERWINDOWRELEASE_BOX_H

#include "../Cartesian3.h"
#include "aarect.h"
#include "HittableList.h"

//in real world, we need box, this class if used for defining box objectsInScene.
class Box : public HittableObject  {
public:
    Box() {}
    Box(const Cartesian3& p0, const Cartesian3& p1, shared_ptr<Material> material);

    virtual bool hitTest(const Ray& r, double t_min, double t_max, HitRecord& rec) override;

    virtual bool boundingBox(double time0, double time1, AABBStructure& outputBox) override;

public:
    // for a box, we only need to know the minimum and maximum points, then we can build a box.
    Cartesian3 boxMin; //the minimum point of a box
    Cartesian3 boxMax; //the maximum point of a box
    HittableList sides;
};


#endif //RAYTRACERENDERWINDOWRELEASE_BOX_H
