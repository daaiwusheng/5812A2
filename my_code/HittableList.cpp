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

void HittableList::add(shared_ptr<HittableObject> object)
{
    objectsInScene.push_back(object);
}

bool HittableList::hitTest(const Ray& r, double t_min, double t_max, HitRecord& rec)
{
    HitRecord tempRecord;
    bool ifHitAnything = false;
    auto closest_t = t_max;
    //the idea is if anyone is hit by the Ray, and we will store the t in closest_t.
    //next loop we will use closest_t as the upper limit. then if the next theObject is hit,
    //we can get a new t less than the previous one. if not, we ignore it.
    //so at the end, we can get the closest theObject hit by the Ray.
    for (const auto& object : objectsInScene) {
        if (object->hitTest(r, t_min, closest_t, tempRecord)) {
            ifHitAnything = true;
            closest_t = tempRecord.t;
            rec = tempRecord;
        }
    }

    return ifHitAnything;
}

bool HittableList::boundingBox(AABBStructure& outputBox)
{
    if (objectsInScene.empty()) return false;

    AABBStructure tempBox;
    bool isFirstBox = true;

    for (const auto& object : objectsInScene) {
        if (!object->boundingBox(tempBox)) {
            //in the if statement, every time we can get a bounding box of the current theObject.
            //if not we can not use this function, in this programme it's illegal.
            return false;
        }
        //if it is the first time getting in this loop, we just set output Box as the tempBox.
        //the later loops, we can combine the previous output Box and the tempBox, then
        //get a bigger box to contain them. that's what we want.
        outputBox = isFirstBox ? tempBox : getSurroundingBox(outputBox, tempBox);
        isFirstBox = false;
    }

    return true;
}








