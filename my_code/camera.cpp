//
// Created by 王宇 on 2022/1/19.
//

#include "camera.h"
//#include "vec3.h"
#include "utility.h"

ray camera::get_ray(double s, double t) const {
    //rd 是在镜头上面随机的点
    Cartesian3 rd = lens_radius * random_in_unit_disk();
    //offset 是按rd进行的偏移量
    Cartesian3 offset = u * rd.x + v * rd.y;

    return ray(
            origin + offset, //同样,光线原点也要进行便宜
            lower_left_corner + s*horizontal + t*vertical - origin - offset, //理解为-(origin+offset)
            random_double(time0, time1)
    );
}

camera::camera(Cartesian3 lookfrom, Cartesian3 lookat, Cartesian3 vup, double vfov, double aspect_ratio, double aperture,
               double focus_dist, double _time0, double _time1) {
    auto theta = degrees_to_radians(vfov);
    auto h = tan(theta/2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

    lens_radius = aperture / 2;
    time0 = _time0;
    time1 = _time1;

}