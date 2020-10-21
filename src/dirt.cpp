#include "dirt.hpp"

#include <SDL.h>

Dirt::Dirt(MoleApp *const app) : image{app, "assets/dirt.png"}, Object{app}
{
    fill();
}

void Dirt::fill()
{
    for (unsigned char i = 0; i < LOADED_TILES; i++)
    {
        app->tiles[(i + (int)app->scroll) % LOADED_TILES] = perlin::row(i + app->scroll);
    }
}

void Dirt::addRow()
{
    app->tiles[(TILE_HEIGHT + app->tile_scroll) % LOADED_TILES] = perlin::row(TILE_HEIGHT + app->tile_scroll + 1);
}

const int Dirt::render() const
{
    int error, code{0};
    double int_part, fract_part{modf(app->scroll, &int_part)};
    char texture;
    SDL_Rect src, dst;

    for (unsigned char i = 0; i <= TILE_HEIGHT; ++i)
    {
        for (unsigned char j = 0; j < TILE_WIDTH; ++j)
        {
            if (not(app->tiles[int(i + int_part) % LOADED_TILES] & 1 << j))
            {
                continue;
            }
            texture = TEXTURE_HASH(i + (int)app->scroll, j);
            src = SDL_Rect{TILE_TEXTURE_SIZE * texture, 0, TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE};
            dst = SDL_Rect{j * TILE_SIZE - 1 * TEXTURE_PIXEL, (i - fract_part) * TILE_SIZE - 1 * TEXTURE_PIXEL, TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE};
            code = image.render(&src, &dst);
            if (code != 0)
            {
                error = code;
            }
        }
    }
    return error;
}