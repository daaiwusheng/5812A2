//
// Created by 王宇 on 2022/1/19.
//

#include "HittableObject.h"
#include "utility.h"
#include "../Cartesian3.h"


double HittableObject::pdf_value(const Cartesian3 &o, const Cartesian3 &v) {
    return 0.0;
}

Cartesian3 HittableObject::random(const Cartesian3 &o) {
    return Cartesian3(1, 0, 0);
}

bool Translate::hitTest(const Ray& r, double t_min, double t_max, HitRecord& rec) {
    //when we need to move the object, we can cheat. like just move the Ray origin to the
    //opposite direction.
    Ray moved_ray(r.origin() - offset, r.direction(), r.time());
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

rotate_y::rotate_y(shared_ptr<HittableObject> _object, double angle) : theObject(_object) {
    auto radians = degreesToRadians(angle);
    sinTheta = sin(radians);
    cosTheta = cos(radians);
    ifHaveBox = theObject->boundingBox(0, 1, aabbbox);

    Cartesian3 minPoint(infinity, infinity, infinity);
    Cartesian3 maxPoint(-infinity, -infinity, -infinity);

    //here it's important and tricky, by the three layers loop, we can get the new bounding box
    //after rotating. we need to check two x, two y and two z.
    //so we need the three-layer loop. every loop we can get the minimum x and maximum y relatively.
    //finally, we can get the lower and upper limit points of the bounding box.
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i * aabbbox.max().x + (1 - i) * aabbbox.min().x;
                auto y = j * aabbbox.max().y + (1 - j) * aabbbox.min().y;
                auto z = k * aabbbox.max().z + (1 - k) * aabbbox.min().z;

                auto new_x = cosTheta * x + sinTheta * z;
                auto new_z = -sinTheta * x + cosTheta * z;

                Cartesian3 candidatePoint(new_x, y, new_z);

                for (int n = 0; n < 3; n++) {
                    minPoint[n] = fmin(minPoint[n], candidatePoint[n]);
                    maxPoint[n] = fmax(maxPoint[n], candidatePoint[n]);
                }
            }
        }
    }

    aabbbox = AABBStructure(minPoint, maxPoint);
}

bool rotate_y::hitTest(const Ray& r, double t_min, double t_max, HitRecord& rec)  {
    auto origin = r.origin();
    auto direction = r.direction();
    //doing the hit test for a rotated object. we also can cheat, like just rotate
    //the Ray.
    origin[0] = cosTheta * r.origin()[0] - sinTheta * r.origin()[2];
    origin[2] = sinTheta * r.origin()[0] + cosTheta * r.origin()[2];

    direction[0] = cosTheta * r.direction()[0] - sinTheta * r.direction()[2];
    direction[2] = sinTheta * r.direction()[0] + cosTheta * r.direction()[2];

    Ray rotatedRay(origin, direction, r.time());

    if (!theObject->hitTest(rotatedRay, t_min, t_max, rec))
        return false;

    auto p = rec.p;
    auto normal = rec.normal;

    p[0] = cosTheta * rec.p[0] + sinTheta * rec.p[2];
    p[2] = -sinTheta * rec.p[0] + cosTheta * rec.p[2];

    normal[0] = cosTheta * rec.normal[0] + sinTheta * rec.normal[2];
    normal[2] = -sinTheta * rec.normal[0] + cosTheta * rec.normal[2];
    //when we store the hit point p and normal, we need to rotate them.
    rec.p = p;
    rec.setFaceNormal(rotatedRay, normal);

    return true;
}

bool rotate_y::boundingBox(double time0, double time1, AABBStructure &outputBox) {
    outputBox = aabbbox;
    return ifHaveBox;
}


bool flipAFace::hitTest(const Ray &r, double t_min, double t_max, HitRecord &rec) {

    if (!theObject->hitTest(r, t_min, t_max, rec))
        return false;
    //easy to explain, in graphics, the direction is determined by the direction of the normal.
    //so we just need to set if the current face is the front face.
    rec.frontFace = !rec.frontFace;
    return true;
}

bool flipAFace::boundingBox(double time0, double time1, AABBStructure &outputBox) {
    return theObject->boundingBox(time0, time1, outputBox);
}


