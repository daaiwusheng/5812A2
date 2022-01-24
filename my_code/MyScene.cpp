//
// Created by 王宇 on 2022/1/23.
//

#include "MyScene.h"
#include "aarect.h"
#include "Box.h"
#include "Sphere.h"

MyOwnScene::MyOwnScene() {
    background = Cartesian3(0,0,0);
    lookfrom = Cartesian3(278, 278, -800);
    lookat = Cartesian3(278, 278, 0);
    vup = Cartesian3(0, 1, 0);
}

HittableList MyOwnScene::getMyOwnScene() {
    HittableList objects;

    auto red   = make_shared<LambertianMaterial>(Cartesian3(.65, .05, .05));
    auto white = make_shared<LambertianMaterial>(Cartesian3(.73, .73, .73));
    auto green = make_shared<LambertianMaterial>(Cartesian3(.12, .45, .15));
    auto light = make_shared<DiffuseLightMaterial>(Cartesian3(15, 15, 15));

    objects.add(make_shared<yz_rectangle>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<yz_rectangle>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<flipAFace>(make_shared<xz_rectangle>(213, 343, 227, 332, 554, light)));
    objects.add(make_shared<xz_rectangle>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<xz_rectangle>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<xy_rectangle>(0, 555, 0, 555, 555, white));

    shared_ptr<HittableObject> box1 = make_shared<Box>(Cartesian3(0,0,0), Cartesian3(165,330,165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<Translate>(box1, Cartesian3(265, 0, 295));
    objects.add(box1);

    shared_ptr<HittableObject> box2 = make_shared<Box>(Cartesian3(0,0,0), Cartesian3(165,165,165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<Translate>(box2, Cartesian3(130, 0, 65));
    objects.add(box2);

    auto material2 = make_shared<LambertianMaterial>(Cartesian3(0.4, 0.2, 0.1));
    objects.add(make_shared<Sphere>(Cartesian3(160, 225, 165), 60, material2));


    return objects;
}
