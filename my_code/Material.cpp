//
// Created by 王宇 on 2022/1/19.
//

#include "Material.h"
#include "Ray.h"
#include "OrthonormalBasis.h"
#include "HittableObject.h"
#include "headers.h"
#include "utility.h"
#include "../Cartesian3.h"

bool Material::scatter(const Ray &ray_in, HitRecord &rec, Cartesian3 &_albedo, Ray &scattered, double &proDenF) const {
    return false;
}

double Material::scattering_proDenF(const Ray &ray_in, const HitRecord &rec, const Ray &scattered) const {
    return 0;
}

Cartesian3 Material::emits(const Ray &ray_in, const HitRecord &rec, double u, double v, const Cartesian3 &p) const {
    return Cartesian3(0,0,0);
}

LambertianMaterial::LambertianMaterial(const Cartesian3 &a_color) : albedo(make_shared<solidColor>(a_color)) {

}

LambertianMaterial::LambertianMaterial(shared_ptr<texture> a_texture) : albedo(a_texture) {

}

bool LambertianMaterial::scatter(const Ray &ray_in,HitRecord &rec, Cartesian3 &_albedo, Ray &scattered, double &proDenF) const {
    OrthonormalBasis uvw;
    uvw.buildFromNormal(rec.normal);
    auto direction = uvw.local(randomCosineDirection());
    //for calculating proDenF of the current scattered Ray, we need an
    //orthogonal rectangular coordinate system at the hit point via the normal.
    //how and why we need the proDenF is explained in Raytracer.cpp.
    scattered = Ray(rec.p, unit_vector(direction));
    _albedo = albedo->value(rec.u, rec.v, rec.p);
    proDenF = dot(uvw.w(), scattered.direction()) / pi;
    return true;
}

double LambertianMaterial::scattering_proDenF(const Ray &ray_in, const HitRecord &rec, const Ray &scattered) const {
    //this is about math, honestly I refered this knowledge online.
    auto cosine = dot(rec.normal, unit_vector(scattered.direction()));
    return cosine < 0 ? 0 : cosine/pi;
}

MetalMaterial::MetalMaterial(const Cartesian3 &_albedo, double _fuzzy) : albedo(_albedo), fuzz(_fuzzy < 1 ? _fuzzy : 1) {

}

bool MetalMaterial::scatter(const Ray &ray_in, HitRecord &rec, Cartesian3 &attenuation, Ray &scattered, double &proDenF) const {
    Cartesian3 reflected = reflect(unit_vector(ray_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * randomInUnitSphere());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}



DielectricMaterial::DielectricMaterial(double refractionIndex) : factor_ref(refractionIndex) {

}

bool DielectricMaterial::scatter(const Ray &ray_in, HitRecord &rec, Cartesian3 &attenuation, Ray &scattered, double &proDenF) const {
    attenuation = Cartesian3(1.0, 1.0, 1.0);

    double refraction_ratio = rec.frontFace ? (1.0 / factor_ref) : factor_ref;

    Cartesian3 unit_direction = unit_vector(ray_in.direction());

    double cos_theta = fmin(dot(-1*unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannotRefract = refraction_ratio * sin_theta > 1.0;
    Cartesian3 direction;

    if (cannotRefract || reflectance(cos_theta, refraction_ratio) > randomDouble())
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, refraction_ratio);
    rec.specular = true;
    scattered = Ray(rec.p, direction);
    return true;
}

double DielectricMaterial::scattering_proDenF(const Ray &ray_in, const HitRecord &rec, const Ray &scattered) const {
    return 0.0;
}

double DielectricMaterial::reflectance(double cosine, double refIdx) {
    //this is about math, honestly I refer online.
    auto r0 = (1 - refIdx) / (1 + refIdx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

DiffuseLightMaterial::DiffuseLightMaterial(shared_ptr<texture> a_texture) : emitMaterial(a_texture) {

}

DiffuseLightMaterial::DiffuseLightMaterial(Cartesian3 a_color) : emitMaterial(make_shared<solidColor>(a_color)) {

}

bool DiffuseLightMaterial::scatter(const Ray &ray_in, HitRecord &rec, Cartesian3 &attenuation, Ray &scattered, double &proDenF) const {
    return false;
}

Cartesian3 DiffuseLightMaterial::emits(const Ray &ray_in, const HitRecord &rec, double u, double v, const Cartesian3 &p) const {

    if (rec.frontFace)
        return emitMaterial->value(u, v, p);
    else
        return Cartesian3(0,0,0);
}