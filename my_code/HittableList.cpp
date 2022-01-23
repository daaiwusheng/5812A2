//
// Created by 王宇 on 2022/1/19.
//

#include "HittableList.h"

HittableList::HittableList()
{

}

HittableList::HittableList(shared_ptr<HittableObject> object)
{
    add(object);
}

void HittableList::clear()
{
    objects.clear();
}

void HittableList::add(shared_ptr<HittableObject> object)
{
    objects.push_back(object);
}

bool HittableList::hitTest(const ray& r, double t_min, double t_max, HitRecord& rec)
{
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hitTest(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

bool HittableList::boundingBox(double time0, double time1, AABBStructure& output_box)
{
    if (objects.empty()) return false;

    AABBStructure temp_box;
    bool first_box = true;

    for (const auto& object : objects) {
        if (!object->boundingBox(time0, time1, temp_box)) return false;
        output_box = first_box ? temp_box : getSurroundingBox(output_box, temp_box);
        first_box = false;
    }

    return true;
}








