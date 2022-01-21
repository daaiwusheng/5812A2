//
// Created by 王宇 on 2022/1/20.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_RAYTRACER_H
#define RAYTRACERENDERWINDOWRELEASE_RAYTRACER_H

#include "vec3.h"
#include "../RGBAImage.h"
#include "../RenderParameters.h"
class ray;
class hittable;


class Raytracer
{
public:
    Raytracer(RenderParameters *renderParameters);
    void render();
    RGBAImage frameBuffer;
    RenderParameters *renderParameters;
private:
    color ray_color(const ray& r, const color& background, const hittable& world, int depth);
    void test_render();
};



#endif //RAYTRACERENDERWINDOWRELEASE_RAYTRACER_H
