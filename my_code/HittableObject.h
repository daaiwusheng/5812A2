//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_HITTABLEOBJECT_H
#define RAYTRACERENDERWINDOWRELEASE_HITTABLEOBJECT_H

#include "Ray.h"
#include "headers.h"
#include "Material.h"
#include "AABBStructure.h"
#include "../Cartesian3.h"

//the struct is a container storing some data if a Ray hits an theObject.
struct HitRecord {
    Cartesian3 p; //the hit point
    Cartesian3 normal; //the normal of the hit point
    shared_ptr<Material> material; //the material of the hit point
    double t; //t is the factor of the equation of the Ray.
    double u;
    double v;
    bool frontFace; //if the hit face is the front, the value is true.
    bool specular = false;
    inline void setFaceNormal(const Ray& r, const Cartesian3& outwardNormal) {
        frontFace = dot(r.direction(), outwardNormal) < 0;
        //we need the normal of the front face. so we need to inverse it if is not the front face.
        normal = frontFace ? outwardNormal : -1 * outwardNormal;
    }
};
//the virtual class of all objects can be hit.
//this class only provides the two APIs.
class HittableObject {
public:
    virtual bool hitTest(const Ray& r, double t_min, double t_max, HitRecord& rec) = 0;
    virtual bool boundingBox(double time0, double time1, AABBStructure& outputBox) = 0;
};

//the Translate class is a tool when we want to translate an object in our scene.
//please see the details in .cpp.
class Translate : public HittableObject {
public:
    Translate(shared_ptr<HittableObject> p, const Cartesian3& displacement)
            : theObject(p), offset(displacement) {}

    virtual bool hitTest(
            const Ray& r, double t_min, double t_max, HitRecord& rec) override;

    virtual bool boundingBox(double time0, double time1, AABBStructure& outputBox) override;

public:
    shared_ptr<HittableObject> theObject;
    Cartesian3 offset; //the offset value for moving
};


class rotate_y : public HittableObject {
public:
    rotate_y(shared_ptr<HittableObject> _object, double angle);

    virtual bool hitTest(
            const Ray& r, double t_min, double t_max, HitRecord& rec) override;

    virtual bool boundingBox(double time0, double time1, AABBStructure& outputBox) override;

public:
    shared_ptr<HittableObject> theObject;
    double sinTheta;
    double cosTheta;
    bool ifHaveBox;
    AABBStructure aabbbox;
};

//in cornell box, we need the area light sending rays down.
//so we need flip the face, then we can build this tool class.
class flipAFace : public HittableObject {
public:
    flipAFace(shared_ptr<HittableObject> p) : theObject(p) {}

    virtual bool hitTest(
            const Ray& r, double t_min, double t_max, HitRecord& rec)  override;

    virtual bool boundingBox(double time0, double time1, AABBStructure& outputBox) override;

public:
    shared_ptr<HittableObject> theObject;
};


#endif //RAYTRACERENDERWINDOWRELEASE_HITTABLEOBJECT_H
