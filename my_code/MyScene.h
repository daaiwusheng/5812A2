//
// Created by 王宇 on 2022/1/23.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_MYSCENE_H
#define RAYTRACERENDERWINDOWRELEASE_MYSCENE_H

#include "HittableList.h"
#include "../Cartesian3.h"

class MyOwnScene{
public:
    const double aspectRatio = 1.0 / 1.0;
    const int imageWidth = 600;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 500; //this is the number of samples from one pixel
    const int maxDepth = 50; //control the depth of Monte Carlo recursive scattering

    Cartesian3 background; //background color of the scene
    //Camera parameters
    Cartesian3 lookFrom;
    Cartesian3 lookAt;
    Cartesian3 vup;
    double distToFocus = 10.0;
    double aperture = 0.0;
    double verticalFieldOfView = 40.0;
    double time0 = 0.0;
    double time1 = 1.0;

    MyOwnScene();
    HittableList getMyOwnScene();

};



#endif //RAYTRACERENDERWINDOWRELEASE_MYSCENE_H
