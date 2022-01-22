//
// Created by 王宇 on 2022/1/21.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_TRIANGLEMESH_H
#define RAYTRACERENDERWINDOWRELEASE_TRIANGLEMESH_H

#include "hittable.h"
#include "../TexturedObject.h"
#include "Material.h"
#include "TransformTool.h"

class TriangleMesh : public hittable
{
public:
    TriangleMesh(const TexturedObject & textureObject,const std::shared_ptr<Material> & material);

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) override;

    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;


    auto intersectsWithTriangle(const Cartesian3& v0,const Cartesian3& v1,const Cartesian3& v2, const ray &ray, double minT,double maxT,int32_t index) -> hit_record &;

private:
    TexturedObject textureObject;
    std::shared_ptr<Material> material;
    TransformTool transformTool;
};


#endif //RAYTRACERENDERWINDOWRELEASE_TRIANGLEMESH_H
