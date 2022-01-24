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

// just give a solid color as the texture.
class solid_color : public texture {
public:
    solid_color();
    solid_color(Cartesian3 c);

    solid_color(double red, double green, double blue);

    virtual Cartesian3 value(double u, double v, const Cartesian3& p) const override;

private:
    Cartesian3 color_value;
};

#endif //RAYTRACERENDERWINDOWRELEASE_TEXTURE_H
