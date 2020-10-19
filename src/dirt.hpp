#pragma once

#include "object.hpp"
#include "components.hpp"
#include "imagehelper.hpp"

#define TEXTURE_HASH(i, j) int((i+j)*(i+j+1)/2+i) % 4

#include <cmath>

class MoleApp;

class Dirt: public RenderComponent, public Object
{
public:
    Dirt(MoleApp * const app);
    ~Dirt( ) { };

    const int render( ) const override;

private:
    const ImageHelper image;

};