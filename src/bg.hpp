#pragma once

#include "object.hpp"
#include "rendercomponent.hpp"
#include "imagehelper.hpp"

#define FOREGROUND_SCROLL 1.0/2.0
#define BACKGROUND_SCROLL 1.0/3.0

class MoleApp;

class Background: public RenderComponent, public Object
{
public:
    Background(MoleApp * const app);

    const int render() const;

private:
    const ImageHelper image;

};