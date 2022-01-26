//
// Created by 王宇 on 2022/1/20.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_RAYTRACER_H
#define RAYTRACERENDERWINDOWRELEASE_RAYTRACER_H

#include "../Cartesian3.h"
#include "../RGBAImage.h"
#include "../RenderParameters.h"
#include "../TexturedObject.h"
#include <memory>

class Ray;
class HittableObject;
class HittableList;

//the class contain the core functions for render and recursive ray tracing.
class Raytracer
{
public:
    Raytracer(RenderParameters *renderParameters,TexturedObject *texturedObject);
    void render();
    RGBAImage frameBuffer;
    RenderParameters *renderParameters;
    TexturedObject *texturedObject;
private:
    Cartesian3 traceRayColor(const Ray& ray, const Cartesian3& background, HittableList currentScene,std::shared_ptr<HittableObject>& lights,int depth);

};



#endif //RAYTRACERENDERWINDOWRELEASE_RAYTRACER_H
