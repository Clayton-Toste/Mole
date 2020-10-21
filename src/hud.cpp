#include "hud.hpp"

HUD::HUD(MoleApp *const app) : proton_counter{app}, neutron_counter{app}, image{app, "assets/collectables_hud.png"}, Object{app}
{
    update_counters();
}

void HUD::update_counters()
{
    std::string protons = std::to_string(app->protons);
    std::string neutrons = std::to_string(app->neutrons);
    proton_counter.setText(protons.c_str(), FONT_SIZE);
    neutron_counter.setText(neutrons.c_str(), FONT_SIZE);
}

const int HUD::render() const
{
    int error, code{0};
    SDL_Rect src, dst;

    src = SDL_Rect{0, 0, TILE_SIZE / 2, TILE_SIZE / 2};
    dst = SDL_Rect{COUNTER_PADDING, COUNTER_PADDING, TILE_SIZE / 2, TILE_SIZE / 2};
    code = image.render(&src, &dst);
    if (code != 0)
    {
        error = code;
    }

    src.w = neutron_counter.getImage()->w;
    dst.x = TILE_SIZE / 2 + COUNTER_PADDING * 2;
    dst.w = neutron_counter.getImage()->w;
    code = neutron_counter.render(&src, &dst);
    if (code != 0)
    {
        error = code;
    }

    src.w = proton_counter.getImage()->w;
    dst.y = TILE_SIZE / 2 + COUNTER_PADDING * 2;
    dst.w = proton_counter.getImage()->w;
    code = proton_counter.render(&src, &dst);
    if (code != 0)
    {
        error = code;
    }

    src.x = TILE_SIZE / 2;
    src.w = TILE_SIZE / 2;
    dst.x = COUNTER_PADDING;
    dst.y = TILE_SIZE / 2 + COUNTER_PADDING * 2;
    dst.w = TILE_SIZE / 2;
    code = image.render(&src, &dst);
    if (code != 0)
    {
        error = code;
    }

    return error;
}
