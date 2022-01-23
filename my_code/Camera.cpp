//
// Created by 王宇 on 2022/1/19.
//

#include "Camera.h"
#include "utility.h"



Camera::Camera(Cartesian3 lookFrom, Cartesian3 lookAt, Cartesian3 viewUp, double verticalFieldOfView, double aspectRatio, double aperture,
               double focusDistance, double _time0, double _time1) {
    auto theta = degrees_to_radians(verticalFieldOfView);
    auto h = tan(theta/2);
    auto viewportHeight = 2.0 * h;
    auto viewportWidth = aspectRatio * viewportHeight;

    //we need a coordinate system to calculate the horizontal,vertical and lowerLeftCorner
    w = unit_vector(lookFrom - lookAt);
    u = unit_vector(cross(viewUp, w));
    v = cross(w, u);

    origin = lookFrom;
    horizontal = focusDistance * viewportWidth * u;
    vertical = focusDistance * viewportHeight * v;
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - focusDistance * w;

    lensRadius = aperture / 2;
    time0 = _time0;
    time1 = _time1;

}

ray Camera::getRay(double _u, double _v) const {
    //randomPoint is a random sample on the Camera'_u lens.
    Cartesian3 randomPoint = lensRadius * randomInUnitDisk();
    Cartesian3 offset = u * randomPoint.x + v * randomPoint.y;
    //the ray function will be commented in Ray class.
    return ray(
            origin + offset, //the origin of the ray need to offset, then we can sample better
            lowerLeftCorner + _u * horizontal + _v * vertical - origin - offset, //-(origin+offset)
            random_double(time0, time1)
    );
}