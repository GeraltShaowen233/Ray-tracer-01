#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <stdlib.h>

// Constants

const double infinity = std::numeric_limits<double>::infinity();

const double PI = 3.1415926535897932385;

//FUNCTIONS

inline double degree_to_radians(double degree)
{
    return degree*PI/180.0;

}

inline double random_double()
{
    //return a random value between [0,1)
    return rand()/(RAND_MAX+1.0); 
}

inline double random_double(double min,double max)
{
    return min+(max - min)*random_double();
}

inline double clamp(double x, double min, double max) 
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#include "ray.h"
#include "vec3.h"