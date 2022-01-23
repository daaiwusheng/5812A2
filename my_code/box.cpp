//
// Created by 王宇 on 2022/1/19.
//

#include "box.h"


box::box(const Cartesian3& p0, const Cartesian3& p1, shared_ptr<Material> ptr) {
    box_min = p0;
    box_max = p1;

    sides.add(make_shared<xy_rectangle>(p0.get_x(), p1.get_x(), p0.get_y(), p1.get_y(), p1.get_z(), ptr));
    sides.add(make_shared<xy_rectangle>(p0.get_x(), p1.get_x(), p0.get_y(), p1.get_y(), p0.get_z(), ptr));

    sides.add(make_shared<xz_rectangle>(p0.get_x(), p1.get_x(), p0.get_z(), p1.get_z(), p1.get_y(), ptr));
    sides.add(make_shared<xz_rectangle>(p0.get_x(), p1.get_x(), p0.get_z(), p1.get_z(), p0.get_y(), ptr));

    sides.add(make_shared<yz_rectangle>(p0.get_y(), p1.get_y(), p0.get_z(), p1.get_z(), p1.get_x(), ptr));
    sides.add(make_shared<yz_rectangle>(p0.get_y(), p1.get_y(), p0.get_z(), p1.get_z(), p0.get_x(), ptr));
}

bool box::hit(const ray& r, double t_min, double t_max, HitRecord& rec) {
    return sides.hit(r, t_min, t_max, rec);
}

bool box::bounding_box(double time0, double time1, AABBStructure &output_box) {
    output_box = AABBStructure(box_min, box_max);
    return true;
}