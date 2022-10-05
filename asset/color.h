#pragma once

#include"vec3.h"
#include"MathConstants.h"
#include <iostream>

inline void write_color(char* data,color& pixel_color,int samples_per_pixel)
{
	double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.

    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

	*data =256.0* clamp(r,0,0.999);
	*(data+1) = 256.0* clamp(g,0,0.999);
	*(data+2) = 256.0* clamp(b,0,0.999);
}
