//
// Created by 王宇 on 2022/1/19.
//

#include "AABBStructure.h"

AABBStructure::AABBStructure()
{

}
/***
 * judge if the Ray can hitTest the Box
 * @param r the Ray
 * @param t_min the lower limit of the solution, 
 * @param t_max the upper limit of the solution,
 * @return if hitTest, return ture.
 */
bool AABBStructure::hit(const Ray &r, double t_min, double t_max) const
{
    //how to calculate the intersect points is solving an equation, which is not difficult.
    //Here, the point is covered in our class, how to determine two intervals overlap.
    for (int i = 0; i < 3; i++) 
    {
        auto reciprocal = 1.0f / r.direction()[i];
        auto t0 = (min()[i] - r.origin()[i]) * reciprocal;
        auto t1 = (max()[i] - r.origin()[i]) * reciprocal;
        if (reciprocal < 0.0f)
        {
            std::swap(t0, t1);
            //we should always keep to is less than t1.
        }
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        //here it's a little bit tricky, if the interval of solution previous is not
        //overlap with the interval of current solution, the t_max can not be bigger
        //than t_min. If there is one dimension can not be hitTest by the Ray, we need to
        //say no intersect here.
        if (t_max <= t_min)
        {
            return false;
        }
            
    }
    return true;
}

AABBStructure::AABBStructure(const Cartesian3 &a, const Cartesian3 &b)
{
    minimum = a;
    maximum = b;
}

Cartesian3 AABBStructure::min() const
{
    return minimum;
}

Cartesian3 AABBStructure::max() const
{
    return maximum;
}

/***
 * calculate the surrounding Box of two AABB boxes
 * @param box0
 * @param box1
 * @return
 */
AABBStructure getSurroundingBox(AABBStructure box0, AABBStructure box1) {
    //the result Box is contain box0 and box1,in order to do this, we just need
    //to get the smallest and the biggest point of these two boxes.
    Cartesian3 small(fmin(box0.min().get_x(), box1.min().get_x()),
                 fmin(box0.min().get_y(), box1.min().get_y()),
                 fmin(box0.min().get_z(), box1.min().get_z()));

    Cartesian3 big(fmax(box0.max().get_x(), box1.max().get_x()),
               fmax(box0.max().get_y(), box1.max().get_y()),
               fmax(box0.max().get_z(), box1.max().get_z()));

    return AABBStructure(small, big);
}