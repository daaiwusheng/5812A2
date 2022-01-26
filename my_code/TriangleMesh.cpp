//
// Created by 王宇 on 2022/1/21.
//

#include "TriangleMesh.h"
#include "Material.h"
#include <cmath>

TriangleMesh::TriangleMesh(const TexturedObject &textureObject, const std::shared_ptr<Material> &material) {
    this->textureObject = textureObject;
    this->material = material;
}

bool TriangleMesh::hitTest(const Ray &ray, double t_min, double t_max, HitRecord &rec)  {
    rec.t = INFINITY;
    //get the transform matrix, because we do not know if transform data were updated.
    auto transformMatrix = transformTool.getTransformMatrix();
    for(auto i = 0;i<textureObject.faceVertices.size() ;i++){
        auto & v = textureObject.faceVertices[i];

        auto v0 = transformMatrix * textureObject.vertices[v[0]];
        auto v1 = transformMatrix * textureObject.vertices[v[1]];
        auto v2 = transformMatrix * textureObject.vertices[v[2]];
        //get and update three vertices.
        HitRecord currentHitRecord;

        currentHitRecord = intersectsWithTriangle(v0,v1,v2,ray,t_min,rec.t,i);

        if(currentHitRecord.t < rec.t){
            rec = currentHitRecord;
        }

    }

    if (rec.t<INFINITY){
        return true;
    }

    return false;
}

auto TriangleMesh::intersectsWithTriangle(const Cartesian3 &v0, const Cartesian3 &v1,
                                          const Cartesian3 &v2, const Ray &ray,
                                          double t_min, double t_max, int32_t index) -> HitRecord & {

    //this is about math, and I referred this knowledge online.
    HitRecord currentRecord;
    currentRecord.t = INFINITY;

    auto v0v1 = v1 - v0;
    auto v0v2 = v2 - v0;
    auto pvec = ray.direction().cross(v0v2);
    float delt = v0v1.dot(pvec);

    // Ray and triangle are parallel if delt is close to 0
    if (std::fabs(delt) < 1e-8) return currentRecord;

    float inversDelt = 1 / delt;

    auto tvec = ray.direction() - v0;
    auto u = tvec.dot(pvec) * inversDelt;
    if (u < 0 || u > 1) {
        return currentRecord;
    }

    auto qvec = tvec.cross(v0v1);
    auto v = ray.direction().dot(qvec) * inversDelt;
    if (v < 0 || u + v > 1){
        return currentRecord;
    }

    auto t = v0v2.dot(qvec) * inversDelt;

    if(t < t_max && t > t_min){
        auto normal = v0v1.cross(v0v2); //normal
        currentRecord.t = t;
        currentRecord.normal = normal;
        currentRecord.setFaceNormal(ray, normal);

        auto & coords = textureObject.faceTexCoords[index];
        //get the three parameters in current face.
        auto t0 = textureObject.textureCoords[coords[0]];
        auto t1 = textureObject.textureCoords[coords[1]];
        auto t2 = textureObject.textureCoords[coords[2]];

        //barycentric interpolation coordinates
        auto coordinates = (1 - u - v) * t0 + u * t1 + v * t2;

        currentRecord.u = coordinates.x;
        currentRecord.v = coordinates.y;

        return  currentRecord;
    }
    return currentRecord;
}

bool TriangleMesh::boundingBox(AABBStructure &output_box)
{
    output_box = AABBStructure(Cartesian3(INFINITY,INFINITY,INFINITY),Cartesian3(-INFINITY,-INFINITY,-INFINITY));
    for(auto &v : textureObject.vertices){
        for(int32_t i = 0;i<3;i++){
            if (v[i] < output_box.min()[i]){
                output_box.min()[i] = v[i];
            }

            if (v[i] > output_box.max()[i]){
                output_box.max()[i] = v[i];
            }
        }
    }

    if (output_box.minimum.x<INFINITY || output_box.maximum.x<INFINITY)
    {
        if (transformTool.renderParameters->transformHasUpdated)
        {
            auto transformMatrix = transformTool.getTransformMatrix();
            output_box.minimum = transformMatrix*output_box.minimum;
            output_box.maximum = transformMatrix*output_box.maximum;
        }
        return true;
    }

    return false;
}




