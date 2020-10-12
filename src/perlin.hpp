#pragma once

// Code courtesy of wikipedia

#define PERLIN_CUTOFF 0

#include <math.h>
#include <iostream>


class perlin
{
    /* Function to linearly interpolate between a0 and a1
    * Weight w should be in the range [0.0, 1.0]
    */
    static float interpolate(float a0, float a1, float w) {
        return (1.0f - w)*a0 + w*a1;
    }

    // Use this instead for a smoother appearance
    /*float interpolate(float a0, float a1, float w) {
        return pow(w, 2.0) * (3.0 - 2.0 * w) * (a1 - a0) + a0;
    }*/

    typedef struct {
        float x, y;
    } vector2;

    /* Create random direction vector
    */
    static vector2 randomGradient(int ix, int iy) {
        // Random float. No precomputed gradients mean this works for any number of grid coordinates
        float random = 2920.f * sin(ix * 21942.f + iy * 171324.f + 8912.f) * cos(ix * 23157.f * iy * 217832.f + 9758.f);
        return (vector2) { cos(random), sin(random) };
    }

    // Computes the dot product of the distance and gradient vectors.
    static float dotGridGradient(int ix, int iy, float x, float y) {
        // Get gradient from integer coordinates
        vector2 gradient = randomGradient(ix, iy);

        // Compute the distance vector
        float dx = x - (float)ix;
        float dy = y - (float)iy;

        // Compute the dot-product
        return (dx*gradient.x + dy*gradient.y);
    }

public:
    // Compute Perlin noise at coordinates x, y
    static bool point(int x, int y) {

        float nx = x/8;
        float ny = x/8;

        // Determine grid cell coordinates
        int x0 = (int)nx;
        int x1 = x0 + 1;
        int y0 = (int)ny;
        int y1 = y0 + 1;

        // Determine interpolation weights
        // Could also use higher order polynomial/s-curve here
        float sx = x - (float)x0;
        float sy = y - (float)y0;

        // Interpolate between grid point gradients
        float n0, n1, ix0, ix1, value;

        n0 = dotGridGradient(x0, y0, nx, ny);
        n1 = dotGridGradient(x1, y0, nx, ny);
        ix0 = interpolate(n0, n1, sx);

        n0 = dotGridGradient(x0, y1, nx, ny);
        n1 = dotGridGradient(x1, y1, nx, ny);
        ix1 = interpolate(n0, n1, sx);

        value = interpolate(ix0, ix1, sy);
        return value > PERLIN_CUTOFF;
    }

    static unsigned int row(const int y) {
        const float ny = y/8.0;
        const int y0 = (int)ny;
        const int y1 = y0 + 1;
        const float sy = ny - (float)y0;

        // Interpolate between grid point gradients
        float n0, n1, ix0, ix1, value;
        unsigned int result {0};
        for (int x = 0; x<8; ++x)
        {
            float nx = x/8.0;
            
            n0 = dotGridGradient(0, y0, nx, ny);
            n1 = dotGridGradient(1, y0, nx, ny);
            ix0 = interpolate(n0, n1, nx);

            n0 = dotGridGradient(0, y1, nx, ny);
            n1 = dotGridGradient(1, y1, nx, ny);
            ix1 = interpolate(n0, n1, nx);

            value = interpolate(ix0, ix1, sy);
            std::cout<<value<<',';
            result |= (value < PERLIN_CUTOFF)<<x;
            std::cout<<result<<std::endl;
        }
        return result;
    }
};