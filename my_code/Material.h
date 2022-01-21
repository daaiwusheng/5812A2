//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_MATERIAL_H
#define RAYTRACERENDERWINDOWRELEASE_MATERIAL_H

#include "ray.h"
#include "texture.h"
#include "../Cartesian3.h"

struct hit_record;

class Material {
public:

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, Cartesian3& alb, ray& scattered, double& pdf
    )const;

    virtual double scattering_pdf(
            const ray& r_in, const hit_record& rec, const ray& scattered
    ) const;

    virtual Cartesian3 emitted(const ray& r_in, const hit_record& rec, double u, double v,
                          const Cartesian3& p) const;
};


class lambertian : public Material {
public:
    lambertian(const Cartesian3& a);
    lambertian(shared_ptr<texture> a);


    virtual bool scatter(
            const ray& r_in, const hit_record& rec, Cartesian3& alb, ray& scattered, double& pdf
    ) const override;

    double scattering_pdf(
            const ray& r_in, const hit_record& rec, const ray& scattered
    ) const;
public:
    shared_ptr<texture> albedo;
};

class metal : public Material {
public:
    metal(const Cartesian3& a, double f);

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, Cartesian3& attenuation, ray& scattered, double& pdf
    ) const override;

public:
    Cartesian3 albedo;
    double fuzz;
};

class dielectric : public Material {
public:
    dielectric(double index_of_refraction);

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, Cartesian3& attenuation, ray& scattered, double& pdf
    ) const override;

public:
    double ir; // Index of Refraction
private:
    static double reflectance(double cosine, double ref_idx);
};

class diffuse_light : public Material  {
public:
    diffuse_light(shared_ptr<texture> a);
    diffuse_light(Cartesian3 c);

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, Cartesian3& attenuation, ray& scattered, double& pdf
    ) const override;

    virtual Cartesian3 emitted(const ray& r_in, const hit_record& rec, double u, double v,
                          const Cartesian3& p) const override;

public:
    shared_ptr<texture> emitmaterial;
};

#endif //RAYTRACERENDERWINDOWRELEASE_MATERIAL_H
