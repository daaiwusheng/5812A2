//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_CAMERA_H
#define RAYTRACERENDERWINDOWRELEASE_CAMERA_H

#include "../Cartesian3.h"
#include "Ray.h"

class Camera {
public:
    Camera(
            Cartesian3 lookFrom,
            Cartesian3 lookAt,
            Cartesian3 viewUp,
            double verticalFieldOfView, // the field is in degrees
            double aspectRatio,
            double aperture,
            double focusDistance
    );

    Ray getRay(double _u, double _v) const;

private:
    Cartesian3 origin;
    Cartesian3 lowerLeftCorner;
    Cartesian3 horizontal;
    Cartesian3 vertical;

    Cartesian3 u, v, w;
    double lensRadius; //the Camera's lens radius, we also can ignore it. but the tutorial I studied used this.
};


#endif //RAYTRACERENDERWINDOWRELEASE_CAMERA_H
