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
class solidColor : public texture {
public:
    solidColor();
    solidColor(Cartesian3 color);

    solidColor(double red, double green, double blue);

    virtual Cartesian3 value(double u, double v, const Cartesian3& p) const override;

private:
    Cartesian3 colorValue;
};

#endif //RAYTRACERENDERWINDOWRELEASE_TEXTURE_H
