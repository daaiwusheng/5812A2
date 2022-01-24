//
// Created by 王宇 on 2022/1/19.
//

#include "texture.h"
#include "headers.h"
#include "utility.h"

solid_color::solid_color()
{

}

solid_color::solid_color(Cartesian3 c) : color_value(c)
{

}

solid_color::solid_color(double red, double green, double blue)
        : solid_color(Cartesian3(red,green,blue))
        {

        }

Cartesian3 solid_color::value(double u, double v, const Cartesian3 &p) const
{
    return color_value;
}


