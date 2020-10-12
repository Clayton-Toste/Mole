#pragma once

#include "object.hpp"
#include "rendercomponent.hpp"
#include "imagehelper.hpp"

#define TEXTURE_HASH(i, j) int((i+j)*(i+j+1)/2+i) % 4

#include <cmath>

class MoleApp;

class Dirt: public RenderComponent, public Object
{
public:
    Dirt(MoleApp * const app);

    int render() const;

private:
    static const int textureHash(const int i, const int j);

    const ImageHelper image;

};