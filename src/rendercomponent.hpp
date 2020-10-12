#pragma once

#include <SDL.h>

class RenderComponent
{
public:
    virtual int render() const=0;
};