//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_TEXTURE_H
#define RAYTRACERENDERWINDOWRELEASE_TEXTURE_H

#include "color.h"
#include "headers.h"

class texture {
public:
    virtual color value(double u, double v, const point3& p) const = 0;
};

class solid_color : public texture {
public:
    solid_color();
    solid_color(color c);

    solid_color(double red, double green, double blue);

    virtual color value(double u, double v, const vec3& p) const override;

private:
    color color_value;
};

class checker_texture : public texture {
public:
    checker_texture();

    checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd);

    checker_texture(color c1, color c2);

    virtual color value(double u, double v, const point3& p) const override;

public:
    shared_ptr<texture> odd;
    shared_ptr<texture> even;
};


class image_texture : public texture {
public:
    const static int bytes_per_pixel = 3;

    image_texture();

    image_texture(const char* filename);

    ~image_texture();

    virtual color value(double u, double v, const vec3& p) const override;

private:
    unsigned char *data;
    int width, height;
    int bytes_per_scanline;
};



#endif //RAYTRACERENDERWINDOWRELEASE_TEXTURE_H
