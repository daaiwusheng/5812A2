//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_RAY_H
#define RAYTRACERENDERWINDOWRELEASE_RAY_H

#include "../Cartesian3.h"

//this class is used for model a ray, the equation is covered in our class.
class Ray {
public:
    Ray();
    Ray(const Cartesian3& _origin, const Cartesian3& _direction, double time = 0.0);

    Cartesian3 origin() const;
    Cartesian3 direction() const;
    double time() const;

    Cartesian3 at(double t) const;

public:
    Cartesian3 origin_point;
    Cartesian3 dir_vector;
    double t_move;//this parameter is used for at a time point in a range if the ray is hitting an object.
    //but I have not finished this.
};

#endif //RAYTRACERENDERWINDOWRELEASE_RAY_H
