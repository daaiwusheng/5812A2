//
// Created by 王宇 on 2022/1/21.
//

#include "TriangleMesh.h"
#include "Material.h"


TriangleMesh::TriangleMesh(const TexturedObject &textureObject, const std::shared_ptr<Material> &material) {
    this->textureObject = textureObject;
    this->material = material;
}

bool TriangleMesh::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {




    return false;
}

bool TriangleMesh::bounding_box(double time0, double time1, aabb &output_box) const {




    return false;
}


