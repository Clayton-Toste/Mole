#include "gui.hpp"

GUI::GUI(MoleApp *const app) : proton_counter{app}, neutron_counter{app}, isotope{app}, weight{app}, icons{app, "assets/collectables_hud.png"}, tutorial{app, "assets/tutorial.png"}, game_over{app, "Game Over", 60}, start_over{app, "Press Space to Play Again", 24}, Object{app}
{
    update_counters();
}

void GUI::update_counters()
{
    std::string protons = std::to_string(app->protons);
    std::string neutrons = std::to_string(app->neutrons);
    proton_counter.setText(protons.c_str(), FONT_SIZE);
    neutron_counter.setText(neutrons.c_str(), FONT_SIZE);
}

const int GUI::render() const
{
    int error, code{0};
    SDL_Rect src, dst;
    std::string text;
    switch (app->state)
    {
    case MoleApp::tutorial:
        src = SDL_Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        dst = SDL_Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        error = tutorial.render(&src, &dst);
        break;
    case MoleApp::results:
        src = SDL_Rect{0, 0, game_over.getImage()->w, game_over.getImage()->h};
        dst = SDL_Rect{(SCREEN_WIDTH - game_over.getImage()->w) / 2, 100, game_over.getImage()->w, game_over.getImage()->h};
        code = game_over.render(&src, &dst);
        if (!code)
        {
            error = code;
        }

        text = "You Made: ";
        text += periodicTable[app->protons];
        text += '-'; 
        text += std::to_string(app->protons + app->neutrons);

        isotope.setText(text.c_str());

        src = SDL_Rect{0, 0, isotope.getImage()->w, isotope.getImage()->h};
        dst = SDL_Rect{(SCREEN_WIDTH - isotope.getImage()->w) / 2, 300, isotope.getImage()->w, isotope.getImage()->h};
        code = isotope.render(&src, &dst);
        if (!code)
        {
            error = code;
        }

        text = "One mole of your element weights:";

        weight.setText(text.c_str(), 20);

        src = SDL_Rect{0, 0, weight.getImage()->w, weight.getImage()->h};
        dst = SDL_Rect{(SCREEN_WIDTH - weight.getImage()->w) / 2, 400, weight.getImage()->w, weight.getImage()->h};
        code = weight.render(&src, &dst);
        if (!code)
        {
            error = code;
        }

        text = std::to_string((app->protons + app->neutrons) * AVAGRO_NUMBER);
        text += "e23 Grams";

        weight.setText(text.c_str(), 20);

        src = SDL_Rect{0, 0, weight.getImage()->w, weight.getImage()->h};
        dst = SDL_Rect{(SCREEN_WIDTH - weight.getImage()->w) / 2, 450, weight.getImage()->w, weight.getImage()->h};
        code = weight.render(&src, &dst);
        if (!code)
        {
            error = code;
        }

        src = SDL_Rect{0, 0, start_over.getImage()->w, start_over.getImage()->h};
        dst = SDL_Rect{(SCREEN_WIDTH - start_over.getImage()->w) / 2, 600, start_over.getImage()->w, start_over.getImage()->h};
        code = start_over.render(&src, &dst);
        if (!code)
        {
            error = code;
        }

    case MoleApp::playing:
        src = SDL_Rect{0, 0, TILE_SIZE / 2, TILE_SIZE / 2};
        dst = SDL_Rect{COUNTER_PADDING, COUNTER_PADDING, TILE_SIZE / 2, TILE_SIZE / 2};
        code = icons.render(&src, &dst);
        if (!code)
        {
            error = code;
        }

        src.w = neutron_counter.getImage()->w;
        dst.x = TILE_SIZE / 2 + COUNTER_PADDING * 2;
        dst.w = neutron_counter.getImage()->w;
        code = neutron_counter.render(&src, &dst);
        if (!code)
        {
            error = code;
        }

        src.w = proton_counter.getImage()->w;
        dst.y = TILE_SIZE / 2 + COUNTER_PADDING * 2;
        dst.w = proton_counter.getImage()->w;
        code = proton_counter.render(&src, &dst);
        if (!code)
        {
            error = code;
        }

        src.x = TILE_SIZE / 2;
        src.w = TILE_SIZE / 2;
        dst.x = COUNTER_PADDING;
        dst.y = TILE_SIZE / 2 + COUNTER_PADDING * 2;
        dst.w = TILE_SIZE / 2;
        code = icons.render(&src, &dst);
        if (!code)
        {
            error = code;
        }

        break;
    }
    return error;
}
