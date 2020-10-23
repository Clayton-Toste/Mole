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
    static long double interpolate(long double a0, long double a1, long double w)
    {
        return (1.0f - w) * a0 + w * a1;
    }

    // Use this instead for a smoother appearance
    /*long double interpolate(long double a0, long double a1, long double w) {
        return pow(w, 2.0) * (3.0 - 2.0 * w) * (a1 - a0) + a0;
    }*/

    typedef struct
    {
        long double x, y;
    } vector2;

    /* Create random direction vector
    */
    static vector2 randomGradient(int ix, int iy)
    {
        // Random long double. No precomputed gradients mean this works for any number of grid coordinates
        long double random = 2920.f * sin(ix * 21942.f + iy * 171324.f + 8912.f) * cos(ix * 23157.f * iy * 217832.f + 9758.f);
        return (vector2){cos(random), sin(random)};
    }

    // Computes the dot product of the distance and gradient vectors.
    static long double dotGridGradient(int ix, int iy, long double x, long double y)
    {
        // Get gradient from integer coordinates
        vector2 gradient = randomGradient(ix, iy);

        // Compute the distance vector
        long double dx = x - (long double)ix;
        long double dy = y - (long double)iy;

        // Compute the dot-product
        return (dx * gradient.x + dy * gradient.y);
    }

public:
    // Compute Perlin noise at coordinates x, y
    static bool point(int x, int y)
    {

        long double nx = x / 8;
        long double ny = x / 8;

        // Determine grid cell coordinates
        int x0 = (int)nx;
        int x1 = x0 + 1;
        int y0 = (int)ny;
        int y1 = y0 + 1;

        // Determine interpolation weights
        // Could also use higher order polynomial/s-curve here
        long double sx = x - (long double)x0;
        long double sy = y - (long double)y0;

        // Interpolate between grid point gradients
        long double n0, n1, ix0, ix1, value;

        n0 = dotGridGradient(x0, y0, nx, ny);
        n1 = dotGridGradient(x1, y0, nx, ny);
        ix0 = interpolate(n0, n1, sx);

        n0 = dotGridGradient(x0, y1, nx, ny);
        n1 = dotGridGradient(x1, y1, nx, ny);
        ix1 = interpolate(n0, n1, sx);

        value = interpolate(ix0, ix1, sy);
        return value > PERLIN_CUTOFF;
    }

    static unsigned int row(const int y)
    {
        const long double ny = y / 8.0;
        const int y0 = (int)ny;
        const int y1 = y0 + 1;
        const long double sy = ny - (long double)y0;

        // Interpolate between grid point gradients
        long double n0, n1, ix0, ix1, value;
        unsigned int result{0};
        for (int x = 0; x < 8; ++x)
        {
            long double nx = x / 8.0;

            n0 = dotGridGradient(0, y0, nx, ny);
            n1 = dotGridGradient(1, y0, nx, ny);
            ix0 = interpolate(n0, n1, nx);

            n0 = dotGridGradient(0, y1, nx, ny);
            n1 = dotGridGradient(1, y1, nx, ny);
            ix1 = interpolate(n0, n1, nx);

            value = interpolate(ix0, ix1, sy);
            result |= (value < PERLIN_CUTOFF) << x;
        }
        return result;
    }
};