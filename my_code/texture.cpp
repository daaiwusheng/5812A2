//
// Created by 王宇 on 2022/1/19.
//

#include "texture.h"
#include "headers.h"
#include "rtw_stb_image.h"
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


image_texture::image_texture()
        : data(nullptr), width(0), height(0), bytes_per_scanline(0)
        {}

image_texture::image_texture(const char *filename) {
    auto components_per_pixel = bytes_per_pixel;

    data = stbi_load(
            filename, &width, &height, &components_per_pixel, components_per_pixel);

    if (!data) {
        std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
        width = height = 0;
    }

    bytes_per_scanline = bytes_per_pixel * width;
}

image_texture::~image_texture() {
    delete data;
}

Cartesian3 image_texture::value(double u, double v, const Cartesian3 &p) const {
    // If we have no texture data, then return solid cyan as a debugging aid.
    if (data == nullptr)
        return Cartesian3(0,1,1);

    // Clamp input texture coordinates to [0,1] x [1,0]
    u = clamp(u, 0.0, 1.0);
    v = 1.0 - clamp(v, 0.0, 1.0);  // Flip V to image coordinates

    auto i = static_cast<int>(u * width);
    auto j = static_cast<int>(v * height);

    // Clamp integer mapping, since actual coordinates should be less than 1.0
    if (i >= width)  i = width-1;
    if (j >= height) j = height-1;

    const auto color_scale = 1.0 / 255.0;
    auto pixel = data + j*bytes_per_scanline + i*bytes_per_pixel;

    return Cartesian3(color_scale*pixel[0], color_scale*pixel[1], color_scale*pixel[2]);
}
