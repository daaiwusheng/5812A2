//
// Created by 王宇 on 2022/1/21.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_TRIANGLEMESH_H
#define RAYTRACERENDERWINDOWRELEASE_TRIANGLEMESH_H

#include "hittable.h"
#include "../TexturedObject.h"
#include "Material.h"

class TriangleMesh : public hittable
{
public:
    TriangleMesh(const TexturedObject & textureObject,const std::shared_ptr<Material> & material);

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

private:
    TexturedObject textureObject;
    std::shared_ptr<Material> material;
};


#endif //RAYTRACERENDERWINDOWRELEASE_TRIANGLEMESH_H
