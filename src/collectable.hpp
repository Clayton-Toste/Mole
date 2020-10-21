#pragma once

#include "object.hpp"
#include "components.hpp"
#include "imagehelper.hpp"

#define COLLECTABLE_FREQUENCY 128

#include <cmath>

class MoleApp;

class Collectable : public RenderComponent, public Object
{
public:
    Collectable(MoleApp *const app);
    ~Collectable(){};

    void fill();
    void addRow();
    void collect();

    const int render() const override;

private:
    const ImageHelper image;
};