//
// Created by 王宇 on 2022/1/19.
//

#include "onb.h"

void onb::build_from_w(const vec3& n) {
    axis[2] = unit_vector(n);
    vec3 a = (fabs(w().x()) > 0.9) ? vec3(0,1,0) : vec3(1,0,0);
    axis[1] = unit_vector(cross(w(), a));
    axis[0] = cross(w(), v());
}

onb::onb() {}

vec3 onb::operator[](int i) const { return axis[i]; }

vec3 onb::local(double a, double b, double c) const {
    return a*u() + b*v() + c*w();
}

vec3 onb::local(const vec3 &a) const {
    return a.x()*u() + a.y()*v() + a.z()*w();
}