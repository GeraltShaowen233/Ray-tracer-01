#pragma once

#include <cmath>
#include <corecrt_math.h>
#include <iostream>
#include"MathConstants.h"

using std::sqrt;

class vec3
{
public:
	double e[3];

public:
	vec3() :e{ 0,0,0 } {}
	vec3(double x, double y, double z) :e{ x,y,z } {}
	double x() { return e[0]; }
	double y() { return e[1]; }
	double z() { return e[2]; }

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i)const { return e[i]; }
	double& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3& vec)
	{
		e[0] += vec.e[0];
		e[1] += vec.e[1];
		e[2] += vec.e[2];
		return *this;
	}

	vec3& operator*=(const double d)
	{
		e[0] *= d;
		e[1] *= d;
		e[2] *= d;
		return *this;
	}

	vec3& operator/=(const double t)
	{
		return *this *= 1 / t;
	}

	double length() const
	{
		return sqrt(length_squared());
	}

	double length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline static vec3 random()
	{	
		return vec3(random_double(),random_double(),random_double());
	}

	inline static vec3 random(double min, double max)
	{
    return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
	}

	bool near_zero() const 
	{
        // Return true if the vector is close to zero in all dimensions.
        const double s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

	~vec3() {};


};



inline std::ostream& operator<<(std::ostream& os, const vec3 v)
{
	return os << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const double d,const vec3& v)
{
	return vec3(d * v.e[0], d * v.e[1], d * v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) 
{
	return t * v;
}

inline vec3 operator/(vec3 v, double t) 
{
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) 
{
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) 
{
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 normalize(vec3 v)
{
	return v/v.length();
}



vec3 random_in_unitsphere()
{
	while (true) 
	{

        auto p = vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 random_unit_vector()
{
	return normalize(random_in_unitsphere());
}

vec3 reflect(const vec3& v, const vec3& n) 
{
    return v - 2*dot(v,n)*n;
}

vec3 refrect(const vec3& vec_in,const vec3& n,double radio)
{
	auto cos_theta = fmin(dot(-vec_in, n), 1.0);
	vec3 r_vertical = radio*(vec_in + cos_theta*n);
	vec3 r_parallel = -sqrt(fabs(1.0 - r_vertical.length_squared())) * n;
	return r_parallel+r_vertical;
}

vec3 random_in_unit_disk() 
{
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color

