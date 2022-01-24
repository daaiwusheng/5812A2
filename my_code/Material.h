//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_MATERIAL_H
#define RAYTRACERENDERWINDOWRELEASE_MATERIAL_H

#include "ray.h"
#include "texture.h"
#include "../Cartesian3.h"

struct HitRecord;

//in our ray tracing task, we need three things to determine a color of a material.
//class Material has three virtual functions.
class Material {
public:
    //in this function, we can calculate
    //1:the scattered ray, 2:the albedo for calculating the scattering ray color,
    //3: the proDenF so-called probability density function value of the current scattered ray.
    virtual bool scatter(
            const ray& ray_in, const HitRecord& rec, Cartesian3& _albedo, ray& scattered, double& proDenF
    )const;

    //this function shoulders calculating the probability density function value for material
    //how to use this we can see in Raytracer.cpp
    virtual double scattering_proDenF(
            const ray& ray_in, const HitRecord& rec, const ray& scattered
    ) const;

    //if the material is a light source, we need to implement this function.
    //via this function, we can get the emitted ray color.
    virtual Cartesian3 emits(const ray& ray_in, const HitRecord& rec, double u, double v,
                             const Cartesian3& p) const;
};


class LambertianMaterial : public Material {
public:
    LambertianMaterial(const Cartesian3& a_color);
    LambertianMaterial(shared_ptr<texture> a_texture);

    virtual bool scatter(
            const ray& ray_in, const HitRecord& rec, Cartesian3& _albedo, ray& scattered, double& proDenF
    ) const override;

    double scattering_proDenF(
            const ray& ray_in, const HitRecord& rec, const ray& scattered
    ) const;
public:
    shared_ptr<texture> albedo;
};

class MetalMaterial : public Material {
public:
    MetalMaterial(const Cartesian3& _albedo, double _fuzzy);

    virtual bool scatter(
            const ray& ray_in, const HitRecord& rec, Cartesian3& attenuation, ray& scattered, double& proDenF
    ) const override;

public:
    Cartesian3 albedo;
    double fuzz;
};

class DielectricMaterial : public Material {
public:
    DielectricMaterial(double refractionIndex);

    virtual bool scatter(
            const ray& ray_in, const HitRecord& rec, Cartesian3& attenuation, ray& scattered, double& proDenF
    ) const override;

public:
    double factor_ref; // the Index of Refraction
private:
    static double reflectance(double cosine, double refIdx);
};

class DiffuseLightMaterial : public Material  {
public:
    DiffuseLightMaterial(shared_ptr<texture> a_texture);
    DiffuseLightMaterial(Cartesian3 a_color);

    virtual bool scatter(
            const ray& ray_in, const HitRecord& rec, Cartesian3& attenuation, ray& scattered, double& proDenF
    ) const override;

    virtual Cartesian3 emits(const ray& ray_in, const HitRecord& rec, double u, double v,
                             const Cartesian3& p) const override;

public:
    shared_ptr<texture> emitMaterial;
};

#endif //RAYTRACERENDERWINDOWRELEASE_MATERIAL_H
