//
// Created by 王宇 on 2022/1/19.
//

#include "color.h"
#include "utility.h"
#include <cmath>

RGBAValue getColor(Cartesian3 pixelColor, int samplesPerPixel) {
    auto r = pixelColor.get_x();
    auto g = pixelColor.get_y();
    auto b = pixelColor.get_z();

    if (r != r) r = 0.0;
    if (g != g) g = 0.0;
    if (b != b) b = 0.0;

    // get the average color by dividing the color by the number of samples and using gamma-correct as gamma=2.0.
    auto scale = 1.0 / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);
    //here we should guarantee the r g b is between 0 and 255
    r = static_cast<unsigned char>(256 * clamp(r, 0.0, 0.999));
    g = static_cast<unsigned char>(256 * clamp(g, 0.0, 0.999));
    b = static_cast<unsigned char>(256 * clamp(b, 0.0, 0.999));

    RGBAValue rec =  RGBAValue(r,g,b);
    return rec;
}