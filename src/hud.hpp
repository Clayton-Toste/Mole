#pragma once

#include "object.hpp"
#include "components.hpp"
#include "imagehelper.hpp"

#define FONT_SIZE 20
#define COUNTER_PADDING 10

class MoleApp;

class HUD : public RenderComponent, public Object
{
public:
    HUD(MoleApp *const app);
    ~HUD(){};

    void update_counters();

    const int render() const override;

private:
    const ImageHelper image;

    ImageHelper proton_counter, neutron_counter;
};