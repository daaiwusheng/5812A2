//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_TEXTURE_H
#define RAYTRACERENDERWINDOWRELEASE_TEXTURE_H

#include "color.h"
#include "headers.h"
#include "../Cartesian3.h"

class texture {
public:
    virtual Cartesian3 value(double u, double v, const Cartesian3& p) const = 0;
};

class solid_color : public texture {
public:
    solid_color();
    solid_color(Cartesian3 c);

    solid_color(double red, double green, double blue);

    virtual Cartesian3 value(double u, double v, const Cartesian3& p) const override;

private:
    Cartesian3 color_value;
};

class checker_texture : public texture {
public:
    checker_texture();

    checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd);

    checker_texture(Cartesian3 c1, Cartesian3 c2);

    virtual Cartesian3 value(double u, double v, const Cartesian3& p) const override;

public:
    shared_ptr<texture> odd;
    shared_ptr<texture> even;
};

#endif //RAYTRACERENDERWINDOWRELEASE_TEXTURE_H
