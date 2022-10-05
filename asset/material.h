#pragma once

#include "MathConstants.h"
//#include "hittable.h"

struct hit_record;

class material
{
public:
    virtual bool scatter(const ray& r_in,
                        const hit_record& record,
                        color& attenuation, 
                        ray& scattered) const = 0;

};

class lambertian : public material
{
public:
    color albedo;

public:
    lambertian(const color& a):albedo(a){}

    virtual bool scatter(const ray& r_in,
                        const hit_record& record,
                        color& attenuation, 
                        ray& scattered) const override
                        {
                            auto scatter_direction = record.normal + random_unit_vector();
                            if (scatter_direction.near_zero())scatter_direction = record.normal;
                            scattered = ray(record.hit_point, scatter_direction);
                            attenuation = albedo;

                            return true;
                        }

};

class metal : public material
{
public:
    color albedo;
    double fuzz;

public:
     metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(const ray& r_in,
                        const hit_record& record,
                        color& attenuation, 
                        ray& scattered) const override
                        {
                            vec3 reflectvec = reflect(normalize(r_in.direction()),record.normal);
                            
                            scattered = ray(record.hit_point, reflectvec+fuzz*random_in_unitsphere());
                            attenuation = albedo;

                            return (dot(scattered.direction(), record.normal) > 0);
                        }
};


class dielectric : public material
{

private:
    static double reflectance(double cosine, double refract)
    {
        double r0 = (1-refract)/(1+refract);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    } 

public:
    double ratio_refraction;

public:
     dielectric(double r) :  ratio_refraction(r) {}

    virtual bool scatter(const ray& r_in,
                        const hit_record& record,
                        color& attenuation, 
                        ray& scattered) const override
                        {
                            attenuation = color(1.0, 1.0, 1.0);
                            double refraction_radio = record.front_face ? (1.0/ratio_refraction) : ratio_refraction;

                            vec3 unit_rdir = normalize(r_in.direction());
                            double cos_theta = fmin(dot(-unit_rdir, record.normal), 1.0);
                            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

                            bool cannot_refract = refraction_radio * sin_theta > 1.0;
                            vec3 direction;

                            if (cannot_refract||reflectance(cos_theta, refraction_radio) > random_double())
                               direction = reflect(unit_rdir, record.normal);
                            else
                               direction = refrect(unit_rdir, record.normal, refraction_radio);

                            scattered = ray(record.hit_point,direction);

                            return true;
                        }
};