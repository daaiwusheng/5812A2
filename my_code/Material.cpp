//
// Created by 王宇 on 2022/1/19.
//

#include "Material.h"
#include "ray.h"
#include "onb.h"
#include "HittableObject.h"
#include "headers.h"
#include "utility.h"
#include "../Cartesian3.h"

bool Material::scatter(const ray &r_in, const HitRecord &rec, Cartesian3 &alb, ray &scattered, double &pdf) const {
    return false;
}

double Material::scattering_pdf(const ray &r_in, const HitRecord &rec, const ray &scattered) const {
    return 0;
}

Cartesian3 Material::emitted(const ray &r_in, const HitRecord &rec, double u, double v, const Cartesian3 &p) const {
    return Cartesian3(0,0,0);
}

bool lambertian::scatter(const ray &r_in, const HitRecord &rec, Cartesian3 &alb, ray &scattered, double &pdf) const {
    onb uvw;
    uvw.build_from_w(rec.normal);
    auto direction = uvw.local(random_cosine_direction());

    scattered = ray(rec.p, unit_vector(direction), r_in.time());
    alb = albedo->value(rec.u, rec.v, rec.p);
    pdf = dot(uvw.w(), scattered.direction()) / pi;
    return true;
}

double lambertian::scattering_pdf(const ray &r_in, const HitRecord &rec, const ray &scattered) const {
    auto cosine = dot(rec.normal, unit_vector(scattered.direction()));
    return cosine < 0 ? 0 : cosine/pi;
}

lambertian::lambertian(const Cartesian3 &a) : albedo(make_shared<solid_color>(a)) {

}

lambertian::lambertian(shared_ptr<texture> a) : albedo(a) {

}

bool metal::scatter(const ray &r_in, const HitRecord &rec, Cartesian3 &attenuation, ray &scattered, double &pdf) const {
    Cartesian3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere(), r_in.time());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

metal::metal(const Cartesian3 &a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {

}

dielectric::dielectric(double index_of_refraction) : ir(index_of_refraction) {

}

bool dielectric::scatter(const ray &r_in, const HitRecord &rec, Cartesian3 &attenuation, ray &scattered, double &pdf) const {
    attenuation = Cartesian3(1.0, 1.0, 1.0);
    double refraction_ratio = rec.frontFace ? (1.0 / ir) : ir;

    Cartesian3 unit_direction = unit_vector(r_in.direction());

    double cos_theta = fmin(dot(-1*unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Cartesian3 direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, refraction_ratio);

    scattered = ray(rec.p, direction, r_in.time());

    return true;
}

double dielectric::reflectance(double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

diffuse_light::diffuse_light(shared_ptr<texture> a) : emitmaterial(a) {

}

diffuse_light::diffuse_light(Cartesian3 c) : emitmaterial(make_shared<solid_color>(c)) {

}

bool
diffuse_light::scatter(const ray &r_in, const HitRecord &rec, Cartesian3 &attenuation, ray &scattered, double &pdf) const {
    return false;
}

Cartesian3 diffuse_light::emitted(const ray &r_in, const HitRecord &rec, double u, double v, const Cartesian3 &p) const {

    if (rec.frontFace)
        return emitmaterial->value(u, v, p);
    else
        return Cartesian3(0,0,0);
}