//
// Created by 王宇 on 2022/1/19.
//

#include "Box.h"

Box::Box() {}

Box::Box(const Cartesian3& p0, const Cartesian3& p1, shared_ptr<Material> material) {
    boxMin = p0;
    boxMax = p1;
    //this is easy to explain, we need three pair of sides to build the box.
    //for example, the xy rectangle, we need two x , two y and one z coordinates.
    //I have explained this in AABBStructure file.
    sides.add(make_shared<xy_rectangle>(p0.get_x(), p1.get_x(), p0.get_y(), p1.get_y(), p1.get_z(), material));
    sides.add(make_shared<xy_rectangle>(p0.get_x(), p1.get_x(), p0.get_y(), p1.get_y(), p0.get_z(), material));

    sides.add(make_shared<xz_rectangle>(p0.get_x(), p1.get_x(), p0.get_z(), p1.get_z(), p1.get_y(), material));
    sides.add(make_shared<xz_rectangle>(p0.get_x(), p1.get_x(), p0.get_z(), p1.get_z(), p0.get_y(), material));

    sides.add(make_shared<yz_rectangle>(p0.get_y(), p1.get_y(), p0.get_z(), p1.get_z(), p1.get_x(), material));
    sides.add(make_shared<yz_rectangle>(p0.get_y(), p1.get_y(), p0.get_z(), p1.get_z(), p0.get_x(), material));
}

bool Box::hitTest(const Ray& r, double t_min, double t_max, HitRecord& rec) {
    //sides can do hit test for us, as it is an instance of HittableList.
    // I will explain the details in HittableList.
    return sides.hitTest(r, t_min, t_max, rec);
}

bool Box::boundingBox(AABBStructure &outputBox) {
    //build the bounding box, I explain how to build it in AABBStructure/
    outputBox = AABBStructure(boxMin, boxMax);
    return true;
}


