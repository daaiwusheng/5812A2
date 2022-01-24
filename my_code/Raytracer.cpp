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

Raytracer::Raytracer(RenderParameters *renderParameters,TexturedObject *texturedObject) {
    this->renderParameters = renderParameters;
    this->texturedObject = texturedObject;
}

void Raytracer::render()
{
    HittableList world = HittableList();
    std::shared_ptr<Camera> cam = std::make_shared<Camera>(Cartesian3(278, 278, -800),
                                                           Cartesian3(278, 278, 0), Cartesian3(0, 1, 0), 40,
                                                           1.0, 0.0, 10.0, 0, 0);
    int image_width = 0;
    int image_height = 0;
    Cartesian3 background = Cartesian3(0,0,0);
    int max_depth = 1;
    int samples_per_pixel = 10;
    //康奈尔box
    if (renderParameters->sceneType != CORNEL_BOX)
    {
        //渲染康奈尔box
        CornellBox cornel_box = CornellBox();
        image_width = cornel_box.imageWidth;
        image_height = cornel_box.imageHeight;

        background = cornel_box.background;
        max_depth = cornel_box.maxDepth;
        samples_per_pixel = cornel_box.maxDepth;
        world = cornel_box.getCornellBox();
        cam = std::make_shared<Camera>(cornel_box.lookFrom, cornel_box.lookAt, cornel_box.vup, cornel_box.verticalFieldOfView,
                                       cornel_box.aspectRatio, cornel_box.aperture, cornel_box.distToFocus, cornel_box.time0, cornel_box.time1);
    }
    else{
        //渲染默认的mesh 和 纹理
        MyOwnScene myOwnScene = MyOwnScene();
        image_width = myOwnScene.image_width;
        image_height = myOwnScene.image_height;

        background = myOwnScene.background;
        max_depth = myOwnScene.max_depth;
        samples_per_pixel = myOwnScene.max_depth;
        world = myOwnScene.getMyOwnScene();
        cam = std::make_shared<Camera>(myOwnScene.lookfrom, myOwnScene.lookat, myOwnScene.vup, myOwnScene.vfov,
                                       myOwnScene.aspect_ratio, myOwnScene.aperture, myOwnScene.dist_to_focus, myOwnScene.time0, myOwnScene.time1);
    }


    omp_set_num_threads(8);
    image_width = frameBuffer.width;
    image_height = frameBuffer.height;
#pragma omp parallel
    {
#pragma omp for
        for (int j = image_height - 1; j >= 0; --j) {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                Cartesian3 pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    auto u = (i + randomDouble()) / (image_width - 1);
                    auto v = (j + randomDouble()) / (image_height - 1);
                    ray r = cam->getRay(u, v);
                    pixel_color += ray_color(r, background, world, max_depth);
                }
                RGBAValue current_color = getColor(pixel_color, samples_per_pixel);
                frameBuffer[j][i] = current_color;
            }
        }
    }
    std::cerr << "\nDone.\n";
}

Cartesian3 Raytracer::ray_color(const ray& r, const Cartesian3& background, HittableList world, int depth) {
    HitRecord rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Cartesian3(0,0,0);
    // If the ray hits nothing, return the background color.
    if (!world.hitTest(r, 0.001, infinity, rec))
        return background;

    ray scattered;
    Cartesian3 attenuation;
    Cartesian3 emitted = rec.material->emits(r, rec, rec.u, rec.v, rec.p);

    double pdf;
    Cartesian3 albedo;

    if (!rec.material->scatter(r, rec, albedo, scattered, pdf))
        return emitted;

    auto on_light = Cartesian3(randomDoubleInRange(213, 343), 554, randomDoubleInRange(227, 332));
    auto to_light = on_light - rec.p;
    auto distance_squared = to_light.length_squared();
    to_light = unit_vector(to_light);

    if (dot(to_light, rec.normal) < 0)
        return emitted;

    double light_area = (343-213)*(332-227);
    auto light_cosine = fabs(to_light.y);
    if (light_cosine < 0.000001)
        return emitted;

    pdf = distance_squared / (light_cosine * light_area);
    scattered = ray(rec.p, to_light, r.time());


    return
           emitted
           + albedo * rec.material->scattering_proDenF(r, rec, scattered)
           * ray_color(scattered, background, world, depth-1) / pdf;

}








/*
void Raytracer::test_render()
{

    std::ofstream fileTextureMap;
    fileTextureMap.open("/Users/wangyu/Downloads/test_assignment_2.ppm");

    // Image
    const auto aspectRatio = 1.0 / 1.0;
    const int imageWidth = 600;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxDepth = 50;



    // World
    auto world = getCornellBox();
    color background(0,0,0);
    // Camera
    point3 lookFrom(278, 278, -800);
    point3 lookAt(278, 278, 0);
    vec3 vup(0, 1, 0);
    auto distToFocus = 10.0;
    auto aperture = 0.0;
    auto verticalFieldOfView = 40.0;
    auto time0 = 0.0;
    auto time1 = 1.0;

    fileTextureMap << "P3\n " << imageWidth << " " << imageHeight << " " << "\n255" << std::endl;

    Camera cam(lookFrom, lookAt, vup, verticalFieldOfView, aspectRatio, aperture, distToFocus, time0, time1);
    // Render


    omp_set_num_threads(8);
    frameBuffer.Resize(imageWidth,imageHeight);

//#pragma omp parallel
    {
//#pragma omp for
        for (int j = imageHeight - 1; j >= 0; --j) {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < imageWidth; ++i) {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samplesPerPixel; ++s) {
                    auto u = (i + randomDoubleInRange()) / (imageWidth - 1);
                    auto v = (j + randomDouble()) / (imageHeight - 1);
                    ray r = cam.getRay(u, v);
                    pixel_color += ray_color(r, background, world, maxDepth);
                }
                RGBAValue current_color = getColor(pixel_color, samplesPerPixel);
                frameBuffer[j][i] = current_color;
            }
        }
    }
    for (int j = imageHeight - 1; j >= 0; --j) {
        for (int i = 0; i < imageWidth; ++i) {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            RGBAValue current_color = frameBuffer[j][i];
            fileTextureMap <<static_cast<int>(current_color.red) << ' '
                           <<static_cast<int>(current_color.green) << ' '
                           <<static_cast<int>(current_color.blue)<< '\n';
        }
    }

    fileTextureMap.close();
    std::cerr << "\nDone.\n";
}
 */