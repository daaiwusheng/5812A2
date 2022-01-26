//
// Created by 王宇 on 2022/1/20.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_CORNELLBOX_H
#define RAYTRACERENDERWINDOWRELEASE_CORNELLBOX_H

#include "HittableList.h"
#include "../Cartesian3.h"

class CornellBox{
public:
    const double aspectRatio = 1.0 / 1.0;
    const int imageWidth = 600;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100; //this is the number of samples from one pixel
    const int maxDepth = 30; //control the depth of Monte Carlo recursive scattering

    Cartesian3 background; //background color
    // Camera parameters
    Cartesian3 lookFrom;
    Cartesian3 lookAt;
    Cartesian3 vup;
    double distToFocus = 10.0;
    double aperture = 0.0;
    double verticalFieldOfView = 40.0;

    CornellBox();

    HittableList getCornellBox();

};



#endif //RAYTRACERENDERWINDOWRELEASE_CORNELLBOX_H
