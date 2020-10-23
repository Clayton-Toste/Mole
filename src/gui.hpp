#pragma once

#include "object.hpp"
#include "components.hpp"
#include "imagehelper.hpp"
#include "periodictable.hpp"

#define FONT_SIZE 20
#define COUNTER_PADDING 10

#include <string>

class MoleApp;

class GUI : public RenderComponent, public Object
{
public:
    GUI(MoleApp *const app);
    ~GUI(){};

    void update_counters();

    const int render() const override;

private:
    const ImageHelper icons, tutorial, game_over, start_over;

    mutable ImageHelper proton_counter, neutron_counter, isotope, weight;
};