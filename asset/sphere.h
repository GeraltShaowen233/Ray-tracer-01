#pragma once

#include "hittable.h"
class sphere : public hittable
{
public:
    point3 cen;
    double rd;
    std::shared_ptr<material> mat_ptr;

public:
    sphere(){}
    sphere(point3 center,double radius,std::shared_ptr<material> m):cen(center),rd(radius),mat_ptr(m){}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

};

inline bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    vec3 oc = r.origin() - cen;
    double a = r.direction().length_squared();
    double half_b = dot(r.direction(), oc);
    double c = oc.length_squared() - rd * rd;

    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false;

    double sqrtd = sqrt(discriminant);

    double root = (-half_b - sqrtd) / a;

    if (root < t_min || t_max < root) 
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.hit_point = r.at(root);

    vec3 outward_normal = (rec.hit_point - cen) / rd;
    rec.set_face_normal(r, outward_normal);

    rec.mat_ptr = mat_ptr;

    return true;
}
