//
// Created by 王宇 on 2022/1/19.
//

#include "aabb.h"

aabb::aabb()
{

}

bool aabb::hit(const ray &r, double t_min, double t_max) const {
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / r.direction()[a];
        auto t0 = (min()[a] - r.origin()[a]) * invD;
        auto t1 = (max()[a] - r.origin()[a]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;
}

aabb::aabb(const Cartesian3 &a, const Cartesian3 &b)
{
    minimum = a;
    maximum = b;
}

Cartesian3 aabb::min() const
{
    return minimum;
}

Cartesian3 aabb::max() const
{
    return maximum;
}

aabb surrounding_box(aabb box0, aabb box1) {
    Cartesian3 small(fmin(box0.min().get_x(), box1.min().get_x()),
                 fmin(box0.min().get_y(), box1.min().get_y()),
                 fmin(box0.min().get_z(), box1.min().get_z()));

    Cartesian3 big(fmax(box0.max().get_x(), box1.max().get_x()),
               fmax(box0.max().get_y(), box1.max().get_y()),
               fmax(box0.max().get_z(), box1.max().get_z()));

    return aabb(small, big);
}