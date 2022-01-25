//
// Created by 王宇 on 2022/1/21.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_TRIANGLEMESH_H
#define RAYTRACERENDERWINDOWRELEASE_TRIANGLEMESH_H

#include "HittableObject.h"
#include "../TexturedObject.h"
#include "Material.h"
#include "TransformTool.h"

//TriangleMesh is also a subclass of HittableObject.
//this class read triangle mesh data from textureObject. then check if can be hit by a ray.
//if the triangle mesh is set with a transformation we just need to get the final transform matrix
//from TransformTool, and use it to multiply the vertices.
class TriangleMesh : public HittableObject
{
public:
    TriangleMesh(const TexturedObject & textureObject,const std::shared_ptr<Material> & material);

    virtual bool hitTest(const Ray& r, double t_min, double t_max, HitRecord& rec) override;

    virtual bool boundingBox(double time0, double time1, AABBStructure& output_box) override;


    auto intersectsWithTriangle(const Cartesian3& v0, const Cartesian3& v1, const Cartesian3& v2, const Ray &ray, double t_min, double t_max, int32_t index) -> HitRecord &;

private:
    TexturedObject textureObject;
    std::shared_ptr<Material> material;
    TransformTool transformTool;
};


#endif //RAYTRACERENDERWINDOWRELEASE_TRIANGLEMESH_H
