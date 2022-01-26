//
// Created by 王宇 on 2022/1/20.
//

#include "Raytracer.h"
#include "Camera.h"
#include "omp.h"
#include "../RGBAValue.h"
#include "../RGBAImage.h"
#include "color.h"
#include "HittableObject.h"
#include "utility.h"
#include "../Cartesian3.h"
#include "CornellBox.h"
#include "headers.h"
#include "HittableList.h"
#include "MyScene.h"
#include "ProDenFunction.h"
#include "aarect.h"

Raytracer::Raytracer(RenderParameters *renderParameters,TexturedObject *texturedObject) {
    this->renderParameters = renderParameters;
    this->texturedObject = texturedObject;
}

void Raytracer::render()
{
    HittableList currentScene = HittableList();
    //currentScene is used for storing all objects in a scene.
    std::shared_ptr<Camera> cam = std::make_shared<Camera>(Cartesian3(278, 278, -800),
                                                           Cartesian3(278, 278, 0), Cartesian3(0, 1, 0), 40,
                                                           1.0, 0.0, 10.0, 0, 0);
    int image_width = 0;
    int image_height = 0;
    Cartesian3 background = Cartesian3(0,0,0);
    int max_depth = 1;
    int samplesPerPixel = 10;
    shared_ptr<HittableObject> lights =
            make_shared<xz_rectangle>(213, 343, 227, 332, 554, shared_ptr<Material>());
    //if sceneType is equal to CORNEL_BOX, then we render cornelBox
    if (renderParameters->sceneType == CORNEL_BOX || renderParameters->sceneType =="")
    {
        //cornelBox scene is being loaded
        CornellBox cornelBox = CornellBox();
        background = cornelBox.background;
        max_depth = cornelBox.maxDepth;
        samplesPerPixel = cornelBox.samplesPerPixel;
        currentScene = cornelBox.getCornellBox();
        cam = std::make_shared<Camera>(cornelBox.lookFrom, cornelBox.lookAt, cornelBox.vup, cornelBox.verticalFieldOfView,
                                       cornelBox.aspectRatio, cornelBox.aperture, cornelBox.distToFocus, cornelBox.time0, cornelBox.time1);
    }
    else if (renderParameters->sceneType == MYOWNSCENE){
        //render my own scene if the sceneType is equal to MYOWNSCENE
        MyOwnScene myOwnScene = MyOwnScene();
        background = myOwnScene.background;
        max_depth = myOwnScene.maxDepth;
        samplesPerPixel = myOwnScene.samplesPerPixel;
        currentScene = myOwnScene.getMyOwnScene();
        cam = std::make_shared<Camera>(myOwnScene.lookFrom, myOwnScene.lookAt, myOwnScene.vup, myOwnScene.verticalFieldOfView,
                                       myOwnScene.aspectRatio, myOwnScene.aperture, myOwnScene.distToFocus, myOwnScene.time0, myOwnScene.time1);
    }


    omp_set_num_threads(8); //set the number of threads
    image_width = frameBuffer.width;
    image_height = frameBuffer.height;
    //I used omp to do multi-thread
#pragma omp parallel
    {
#pragma omp for
        for (int j = image_height - 1; j >= 0; --j) {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                Cartesian3 pixel_color(0, 0, 0);
                for (int s = 0; s < samplesPerPixel; ++s) {
                    //even in one pixel we also need a randomDouble() to sample randomly.
                    auto u = (i + randomDouble()) / (image_width - 1);
                    auto v = (j + randomDouble()) / (image_height - 1);
                    Ray r = cam->getRay(u, v); //the ray is from a camera, the view point. then we trace it.
                    pixel_color += traceRayColor(r, background, currentScene,lights,max_depth);
                }
                RGBAValue current_color = getColor(pixel_color, samplesPerPixel);//get the average color for a pixel
                frameBuffer[j][i] = current_color;
            }
        }
    }
    std::cerr << "\nDone.\n";
}

//the recursive ray trace function.
Cartesian3 Raytracer::traceRayColor(const Ray& ray, const Cartesian3& background, HittableList currentScene,shared_ptr<HittableObject>& lights, int depth) {
    HitRecord rec;

    // If we have done more than the Ray bounce limit, we need to stop can return zero color.
    if (depth <= 0){
        return Cartesian3(0,0,0);
    }
    // If the ray hits nothing, just return the background color. as it hits the background
    if (!currentScene.hitTest(ray, 0.001, infinity, rec)) {
        return background;
    }
    Ray scattered;
//    Cartesian3 attenuation;
    Cartesian3 emitted = rec.material->emits(ray, rec, rec.u, rec.v, rec.p);

    double currentProDenF;
    Cartesian3 albedo; //the color of the material. just like attenuation.
    double pdf_val;
    if (!rec.material->scatter(ray, rec, albedo, scattered, currentProDenF)) {
        //if the material does not scatter, then we can say that it is a light source, just
        //return the emitted value as the light color.
        return emitted;
    }

    if(rec.specular){
        return albedo * traceRayColor(scattered, background, currentScene,lights,depth - 1);
    }

    auto p0 = make_shared<hittable_pdf>(lights, rec.p);
    auto p1 = make_shared<CosineProDenF>(rec.normal);
    mixture_pdf mixed_pdf(p0, p1);

    scattered = Ray(rec.p, mixed_pdf.generate(), ray.time());
    pdf_val = mixed_pdf.value(scattered.direction());

    //the return calculating code is very important. it's the equation of raytracing.
    //it's an integration of the equation of raytracing.
    //dividing by currentProDenF is Monte Carlo sampling which can help the integration to be more accurate.
    return
           emitted
           + albedo * rec.material->scattering_proDenF(ray, rec, scattered)
             * traceRayColor(scattered, background, currentScene,lights, depth - 1) / pdf_val;

}


