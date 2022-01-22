//
// Created by 王宇 on 2022/1/20.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_RAYTRACER_H
#define RAYTRACERENDERWINDOWRELEASE_RAYTRACER_H

#include "../Cartesian3.h"
#include "../RGBAImage.h"
#include "../RenderParameters.h"
#include "../TexturedObject.h"
class ray;
class hittable;
class hittable_list;

class Raytracer
{
public:
    Raytracer(RenderParameters *renderParameters,TexturedObject *texturedObject);
    void render();
    RGBAImage frameBuffer;
    RenderParameters *renderParameters;
    TexturedObject *texturedObject;
private:
    Cartesian3 ray_color(const ray& r, const Cartesian3& background, hittable_list world, int depth);
    void test_render();
};



#endif //RAYTRACERENDERWINDOWRELEASE_RAYTRACER_H
