//
// Created by 王宇 on 2022/1/19.
//

#include "texture.h"
#include "headers.h"
#include "utility.h"

solidColor::solidColor()
{

}

solidColor::solidColor(Cartesian3 color) : colorValue(color)
{

}

solidColor::solidColor(double red, double green, double blue)
        : solidColor(Cartesian3(red, green, blue))
        {

        }

Cartesian3 solidColor::value(double u, double v, const Cartesian3 &p) const
{
    return colorValue;
}


