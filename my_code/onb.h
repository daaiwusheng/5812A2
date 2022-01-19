//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_ONB_H
#define RAYTRACERENDERWINDOWRELEASE_ONB_H

#include "vec3.h"

class onb {
public:
    onb();

    inline vec3 operator[](int i) const;

    vec3 u() const { return axis[0]; }
    vec3 v() const { return axis[1]; }
    vec3 w() const { return axis[2]; }

    vec3 local(double a, double b, double c) const;

    vec3 local(const vec3& a) const;

    void build_from_w(const vec3&);

public:
    vec3 axis[3];
};



#endif //RAYTRACERENDERWINDOWRELEASE_ONB_H
