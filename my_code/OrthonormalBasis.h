//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_ORTHONORMALBASIS_H
#define RAYTRACERENDERWINDOWRELEASE_ORTHONORMALBASIS_H

#include "../Cartesian3.h"

class OrthonormalBasis {
public:
    OrthonormalBasis();

    inline Cartesian3 operator[](int i) const;

    Cartesian3 u() const { return axis[0]; }
    Cartesian3 v() const { return axis[1]; }
    Cartesian3 w() const { return axis[2]; }

    Cartesian3 local(double a, double b, double c) const;

    Cartesian3 local(const Cartesian3& a) const;

    void build_from_w(const Cartesian3&);

public:
    Cartesian3 axis[3];
};



#endif //RAYTRACERENDERWINDOWRELEASE_ORTHONORMALBASIS_H
