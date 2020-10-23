#include "collectable.hpp"

#include <SDL.h>

Collectable::Collectable(MoleApp *const app) : image{app, "assets/collectables.png"}, Object{app}
{
    fill();
}

unsigned char hash(unsigned long int n)
{
    n = ((n >> 16) ^ n) * 0x45d9f3b;
    n = ((n >> 16) ^ n) * 0x45d9f3b;
    n = (n >> 16) ^ n;
    return (signed char)n;
}

void Collectable::fill()
{
    unsigned char loc;
    for (unsigned char i = 0; i < LOADED_TILES; i++)
    {
        loc = hash(i + app->tile_scroll);
        app->collectables[(i + app->tile_scroll) % LOADED_TILES] = (signed char)(loc < 16 ? loc : -1);
    }
}

void Collectable::addRow()
{
    unsigned char loc = hash(TILE_HEIGHT + app->tile_scroll);
    app->collectables[(TILE_HEIGHT + app->tile_scroll) % LOADED_TILES] = (signed char)(loc < 16 ? loc : -1);
}

void Collectable::collect()
{
    signed char loc = app->collectables[(app->player->tile_y + app->tile_scroll) % LOADED_TILES];
    if (loc < 0 || (loc ^ app->player->tile_x) & 7)
    {
        return;
    }
    if (loc & 8)
    {
        app->protons++;
    }
    else
    {
        app->neutrons++;
    }
    app->gui->update_counters();
    app->collectables[(app->player->tile_y + app->tile_scroll) % LOADED_TILES] = -1;
}

const int Collectable::render() const
{
    int error, code{0};
    SDL_Rect src, dst;

    for (unsigned char i = 0; i <= TILE_HEIGHT; ++i)
    {
        signed char texture{app->collectables[(int)(app->tile_scroll + i) % LOADED_TILES]};
        if (texture < 0)
        {
            continue;
        }
        src = SDL_Rect{TILE_SIZE * bool(texture & 8), 0, TILE_SIZE, TILE_SIZE};
        dst = SDL_Rect{TILE_SIZE * (texture & 7), (i - app->scroll) * TILE_SIZE - 1 * TEXTURE_PIXEL, TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE};
        code = image.render(&src, &dst);
        if (!code)
        {
            error = code;
        }
    }
    return error;
}