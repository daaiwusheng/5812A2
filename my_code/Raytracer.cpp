//
// Created by 王宇 on 2022/1/20.
//

#include "Raytracer.h"
#include "camera.h"
#include "omp.h"
#include "../RGBAValue.h"
#include "../RGBAImage.h"
#include "color.h"
#include "hittable.h"
#include "utility.h"
#include "../Cartesian3.h"
#include "CornellBox.h"
#include "headers.h"
#include "hittable_list.h"

Raytracer::Raytracer(RenderParameters *renderParameters,TexturedObject *texturedObject) {
    this->renderParameters = renderParameters;
    this->texturedObject = texturedObject;
}

void Raytracer::render()
{
    hittable_list world = hittable_list();
    std::shared_ptr<camera> cam = std::make_shared<camera>(Cartesian3(278, 278, -800),
                                                           Cartesian3(278, 278, 0), Cartesian3(0, 1, 0), 40,
                                                           1.0, 0.0, 10.0, 0, 0);
    int image_width = 0;
    int image_height = 0;
    Cartesian3 background = Cartesian3(0,0,0);
    int max_depth = 1;
    int samples_per_pixel = 10;
    //康奈尔box
    if (renderParameters->sceneType == CORNEL_BOX)
    {
        //渲染康奈尔box
        cornellBox cornel_box = cornellBox();
        image_width = cornel_box.image_width;
        image_height = cornel_box.image_height;

        background = cornel_box.background;
        max_depth = cornel_box.max_depth;
        samples_per_pixel = cornel_box.max_depth;
        world = cornel_box.cornell_box();
        cam = std::make_shared<camera>(cornel_box.lookfrom, cornel_box.lookat, cornel_box.vup, cornel_box.vfov,
                  cornel_box.aspect_ratio, cornel_box.aperture, cornel_box.dist_to_focus, cornel_box.time0, cornel_box.time1);
    }
    else{
        //渲染默认的mesh 和 纹理

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
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam->get_ray(u, v);
                    pixel_color += ray_color(r, background, world, max_depth);
                }
                RGBAValue current_color = get_color(pixel_color, samples_per_pixel);
                frameBuffer[j][i] = current_color;
            }
        }
    }
    std::cerr << "\nDone.\n";
}

Cartesian3 Raytracer::ray_color(const ray& r, const Cartesian3& background, hittable_list world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Cartesian3(0,0,0);
    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    ray scattered;
    Cartesian3 attenuation;
    Cartesian3 emitted = rec.mat_ptr->emitted(r,rec,rec.u,rec.v,rec.p);

    double pdf;
    Cartesian3 albedo;

    if (!rec.mat_ptr->scatter(r, rec, albedo, scattered, pdf))
        return emitted;

    auto on_light = Cartesian3(random_double(213,343), 554, random_double(227,332));
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
           + albedo * rec.mat_ptr->scattering_pdf(r, rec, scattered)
           * ray_color(scattered, background, world, depth-1) / pdf;

}








/*
void Raytracer::test_render()
{

    std::ofstream fileTextureMap;
    fileTextureMap.open("/Users/wangyu/Downloads/test_assignment_2.ppm");

    // Image
    const auto aspect_ratio = 1.0 / 1.0;
    const int image_width = 600;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;



    // World
    auto world = cornell_box();
    color background(0,0,0);
    // Camera
    point3 lookfrom(278, 278, -800);
    point3 lookat(278, 278, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;
    auto vfov = 40.0;
    auto time0 = 0.0;
    auto time1 = 1.0;

    fileTextureMap << "P3\n " << image_width << " " << image_height << " " << "\n255" << std::endl;

    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, time0, time1);
    // Render


    omp_set_num_threads(8);
    frameBuffer.Resize(image_width,image_height);

//#pragma omp parallel
    {
//#pragma omp for
        for (int j = image_height - 1; j >= 0; --j) {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color(r, background, world, max_depth);
                }
                RGBAValue current_color = get_color(pixel_color, samples_per_pixel);
                frameBuffer[j][i] = current_color;
            }
        }
    }
    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
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