//
// Created by 王宇 on 2022/1/19.
//

#include "OrthonormalBasis.h"

OrthonormalBasis::OrthonormalBasis()
{

}

void OrthonormalBasis::build_from_w(const Cartesian3& n) {
    axis[2] = unit_vector(n);
    Cartesian3 a = (fabs(w().x) > 0.9) ? Cartesian3(0,1,0) : Cartesian3(1,0,0);
    axis[1] = unit_vector(cross(w(), a));
    axis[0] = cross(w(), v());
}

Cartesian3 OrthonormalBasis::operator[](int i) const { return axis[i]; }

Cartesian3 OrthonormalBasis::local(double a, double b, double c) const {
    return a*u() + b*v() + c*w();
}

Cartesian3 OrthonormalBasis::local(const Cartesian3 &a) const {
    return a.x*u() + a.y*v() + a.z*w();
}