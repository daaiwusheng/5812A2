//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_ORTHONORMALBASIS_H
#define RAYTRACERENDERWINDOWRELEASE_ORTHONORMALBASIS_H

#include "../Cartesian3.h"

//this is a quite easy tool class, which can build a OrthonormalBasis coordinate system.
class OrthonormalBasis {
public:
    OrthonormalBasis();

    inline Cartesian3 operator[](int i) const;

    Cartesian3 u() const;
    Cartesian3 v() const;
    Cartesian3 w() const;

    Cartesian3 local(double a, double b, double c) const;

    Cartesian3 local(const Cartesian3& a) const;

    void buildFromNormal(const Cartesian3 &n);

public:
    Cartesian3 axis[3];
};



#endif //RAYTRACERENDERWINDOWRELEASE_ORTHONORMALBASIS_H
