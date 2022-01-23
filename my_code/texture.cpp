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

checker_texture::checker_texture()
{

}

checker_texture::checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd)
        : even(_even), odd(_odd)
        {

        }

checker_texture::checker_texture(Cartesian3 c1, Cartesian3 c2)
        : even(make_shared<solid_color>(c1)) , odd(make_shared<solid_color>(c2))
        {

        }

Cartesian3 checker_texture::value(double u, double v, const Cartesian3 &p) const {
    auto sines = sin(10*p.x)*sin(10*p.y)*sin(10*p.z);
    if (sines < 0)
        return odd->value(u, v, p);
    else
        return even->value(u, v, p);
}

