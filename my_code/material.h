//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_MATERIAL_H
#define RAYTRACERENDERWINDOWRELEASE_MATERIAL_H

#include "ray.h"
#include "texture.h"

struct hit_record;

class material {
public:

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& alb, ray& scattered, double& pdf
    )const;

    virtual double scattering_pdf(
            const ray& r_in, const hit_record& rec, const ray& scattered
    ) const;

    virtual color emitted(const ray& r_in, const hit_record& rec, double u, double v,
                          const point3& p) const;
};


class lambertian : public material {
public:
    lambertian(const color& a);
    lambertian(shared_ptr<texture> a);


    virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& alb, ray& scattered, double& pdf
    ) const override;

    double scattering_pdf(
            const ray& r_in, const hit_record& rec, const ray& scattered
    ) const;
public:
    shared_ptr<texture> albedo;
};

class metal : public material {
public:
    metal(const color& a, double f);

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered, double& pdf
    ) const override;

public:
    color albedo;
    double fuzz;
};

class dielectric : public material {
public:
    dielectric(double index_of_refraction);

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered, double& pdf
    ) const override;

public:
    double ir; // Index of Refraction
private:
    static double reflectance(double cosine, double ref_idx);
};

class diffuse_light : public material  {
public:
    diffuse_light(shared_ptr<texture> a);
    diffuse_light(color c);

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered, double& pdf
    ) const override;

    virtual color emitted(const ray& r_in, const hit_record& rec, double u, double v,
                          const point3& p) const override;

public:
    shared_ptr<texture> emitmaterial;
};

#endif //RAYTRACERENDERWINDOWRELEASE_MATERIAL_H
