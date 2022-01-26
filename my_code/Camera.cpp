//
// Created by 王宇 on 2022/1/19.
//

#include "Camera.h"
#include "utility.h"



Camera::Camera(Cartesian3 lookFrom, Cartesian3 lookAt, Cartesian3 viewUp, double verticalFieldOfView, double aspectRatio, double aperture,
               double focusDistance) {
    auto theta = degreesToRadians(verticalFieldOfView);
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


}

Ray Camera::getRay(double _u, double _v) const {
    //randomPoint is a random sample on the Camera'_u lens.
    Cartesian3 randomPoint = lensRadius * randomInUnitDisk();
    Cartesian3 offset = u * randomPoint.x + v * randomPoint.y;
    //the Ray function will be commented in Ray class.
    return Ray(
            origin + offset, //the origin of the Ray need to offset, then we can sample better
            lowerLeftCorner + _u * horizontal + _v * vertical - origin - offset //-(origin+offset)
    );
}