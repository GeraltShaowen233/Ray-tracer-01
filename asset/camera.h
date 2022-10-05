#pragma once

#include "MathConstants.h"

class camera 
{
private:
    point3 origin;
    vec3 plane_x;
    vec3 plane_y;
    point3 lower_left_corner;
    vec3 u, v, w;
    double lens_radius;

public:
    camera(
        point3 lookfrom,
        point3 lookat,
        vec3   vup,
        double v_Fov, // vertical field-of-view in degrees
        double aspect_ratio,
        double aperture,
        double focus_dist
    )
    {
        auto theta = degree_to_radians(v_Fov);
        auto h = tan(theta/2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = normalize(lookfrom - lookat);
        u = normalize(cross(vup, w));
        v = cross(w,u);

        origin = lookfrom;
        plane_x = focus_dist*viewport_width*u;
        plane_y = focus_dist*viewport_height*v;
        lower_left_corner = origin  - plane_x / 2 - plane_y / 2 - focus_dist*w;
        //vector from camera_position to the lower_left_ corner

        lens_radius = aperture / 2;
        
    }

     ray send_ray(double s, double t) const 
     {
            vec3 rd = lens_radius * random_in_unit_disk();
            vec3 offset = u * rd.x() + v * rd.y();

            return ray
            (
                origin + offset,
                lower_left_corner + s*plane_x + t*plane_y - origin - offset
            );
        }
};