//
// Created by 王宇 on 2022/1/19.
//

#include "HittableObject.h"
#include "utility.h"
#include "../Cartesian3.h"

bool translate::hitTest(const ray& r, double t_min, double t_max, HitRecord& rec) {
    ray moved_r(r.origin() - offset, r.direction(), r.time());
    if (!ptr->hitTest(moved_r, t_min, t_max, rec))
        return false;

    rec.p += offset;
    rec.setFaceNormal(moved_r, rec.normal);

    return true;
}

bool translate::boundingBox(double time0, double time1, AABBStructure& outputBox) {
    if (!ptr->boundingBox(time0, time1, outputBox))
        return false;

    outputBox = AABBStructure(
            outputBox.min() + offset,
            outputBox.max() + offset);

    return true;
}

rotate_y::rotate_y(shared_ptr<HittableObject> p, double angle) : ptr(p) {
    auto radians = degrees_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    hasbox = ptr->boundingBox(0, 1, bbox);

    Cartesian3 min( infinity,  infinity,  infinity);
    Cartesian3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i*bbox.max().x + (1-i)*bbox.min().x;
                auto y = j*bbox.max().y + (1-j)*bbox.min().y;
                auto z = k*bbox.max().z + (1-k)*bbox.min().z;

                auto newx =  cos_theta*x + sin_theta*z;
                auto newz = -sin_theta*x + cos_theta*z;

                Cartesian3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    bbox = AABBStructure(min, max);
}

bool rotate_y::hitTest(const ray& r, double t_min, double t_max, HitRecord& rec)  {
    auto origin = r.origin();
    auto direction = r.direction();

    origin[0] = cos_theta*r.origin()[0] - sin_theta*r.origin()[2];
    origin[2] = sin_theta*r.origin()[0] + cos_theta*r.origin()[2];

    direction[0] = cos_theta*r.direction()[0] - sin_theta*r.direction()[2];
    direction[2] = sin_theta*r.direction()[0] + cos_theta*r.direction()[2];

    ray rotated_r(origin, direction, r.time());

    if (!ptr->hitTest(rotated_r, t_min, t_max, rec))
        return false;

    auto p = rec.p;
    auto normal = rec.normal;

    p[0] =  cos_theta*rec.p[0] + sin_theta*rec.p[2];
    p[2] = -sin_theta*rec.p[0] + cos_theta*rec.p[2];

    normal[0] =  cos_theta*rec.normal[0] + sin_theta*rec.normal[2];
    normal[2] = -sin_theta*rec.normal[0] + cos_theta*rec.normal[2];

    rec.p = p;
    rec.setFaceNormal(rotated_r, normal);

    return true;
}

bool rotate_y::boundingBox(double time0, double time1, AABBStructure &outputBox) {
    outputBox = bbox;
    return hasbox;
}


bool flip_face::hitTest(const ray &r, double t_min, double t_max, HitRecord &rec) {

    if (!ptr->hitTest(r, t_min, t_max, rec))
        return false;

    rec.frontFace = !rec.frontFace;
    return true;
}

bool flip_face::boundingBox(double time0, double time1, AABBStructure &outputBox) {
    return ptr->boundingBox(time0, time1, outputBox);
}
