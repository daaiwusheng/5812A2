//
// Created by 王宇 on 2022/1/19.
//

#include "HittableObject.h"
#include "utility.h"
#include "../Cartesian3.h"

bool Translate::hitTest(const ray& r, double t_min, double t_max, HitRecord& rec) {
    //when we need to move the object, we can cheat. like just move the ray origin to the
    //opposite direction.
    ray moved_ray(r.origin() - offset, r.direction(), r.time());
    if (!theObject->hitTest(moved_ray, t_min, t_max, rec))
        return false;
    //but, the hit point we need move to the offset direction. not the opposite.
    rec.p += offset;
    rec.setFaceNormal(moved_ray, rec.normal);

    return true;
}

bool Translate::boundingBox(double time0, double time1, AABBStructure& outputBox) {
    if (!theObject->boundingBox(time0, time1, outputBox))
        return false;
    // as we need to move the object. we just need to move the bounding box by the
    // upper and lower limits.
    outputBox = AABBStructure(
            outputBox.min() + offset,
            outputBox.max() + offset);

    return true;
}

rotate_y::rotate_y(shared_ptr<HittableObject> p, double angle) : theObject(p) {
    auto radians = degrees_to_radians(angle);
    sinTheta = sin(radians);
    cosTheta = cos(radians);
    ifHaveBox = theObject->boundingBox(0, 1, bbox);

    Cartesian3 min( infinity,  infinity,  infinity);
    Cartesian3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i*bbox.max().x + (1-i)*bbox.min().x;
                auto y = j*bbox.max().y + (1-j)*bbox.min().y;
                auto z = k*bbox.max().z + (1-k)*bbox.min().z;

                auto newx = cosTheta * x + sinTheta * z;
                auto newz = -sinTheta * x + cosTheta * z;

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

    origin[0] = cosTheta * r.origin()[0] - sinTheta * r.origin()[2];
    origin[2] = sinTheta * r.origin()[0] + cosTheta * r.origin()[2];

    direction[0] = cosTheta * r.direction()[0] - sinTheta * r.direction()[2];
    direction[2] = sinTheta * r.direction()[0] + cosTheta * r.direction()[2];

    ray rotated_r(origin, direction, r.time());

    if (!theObject->hitTest(rotated_r, t_min, t_max, rec))
        return false;

    auto p = rec.p;
    auto normal = rec.normal;

    p[0] = cosTheta * rec.p[0] + sinTheta * rec.p[2];
    p[2] = -sinTheta * rec.p[0] + cosTheta * rec.p[2];

    normal[0] = cosTheta * rec.normal[0] + sinTheta * rec.normal[2];
    normal[2] = -sinTheta * rec.normal[0] + cosTheta * rec.normal[2];

    rec.p = p;
    rec.setFaceNormal(rotated_r, normal);

    return true;
}

bool rotate_y::boundingBox(double time0, double time1, AABBStructure &outputBox) {
    outputBox = bbox;
    return ifHaveBox;
}


bool flipAFace::hitTest(const ray &r, double t_min, double t_max, HitRecord &rec) {

    if (!theObject->hitTest(r, t_min, t_max, rec))
        return false;

    rec.frontFace = !rec.frontFace;
    return true;
}

bool flipAFace::boundingBox(double time0, double time1, AABBStructure &outputBox) {
    return theObject->boundingBox(time0, time1, outputBox);
}
