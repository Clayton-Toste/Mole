#pragma once

#include <SDL.h>

class RenderComponent
{
public:
    virtual const int render() const=0;
};