//
// Created by 王宇 on 2022/1/19.
//

#include "Ray.h"

Ray::Ray() {

}

Ray::Ray(const Cartesian3 &_origin, const Cartesian3 &_direction, double time)
        : origin_point(_origin), dir_vector(_direction), t_move(time)
{

}

Cartesian3 Ray::origin() const {
    return origin_point;
}

Cartesian3 Ray::direction() const {
    return dir_vector;
}

double Ray::time() const {
    return t_move;
}

Cartesian3 Ray::at(double t) const {
    return origin_point + t * dir_vector;
}
