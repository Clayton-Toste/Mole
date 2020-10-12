#include "dirt.hpp"

#include <SDL.h>

Dirt::Dirt(MoleApp * const app) : image{app, "assets/dirt.png"}, Object{app} { }

const int Dirt::render() const 
{
    unsigned int error {0};
    double int_part;
    double fract_part{modf(app->scroll, &int_part)};
    for (unsigned int i=0; i<=TILE_HEIGHT; ++i)
    {
        for (unsigned int j=0; j<TILE_WIDTH; ++j)
        {
            if (not (app->tiles[int(i+int_part)%LOADED_TILES] & 1<<j))
            {
                continue;
            }
            int texture{TEXTURE_HASH(i+(int)app->scroll, j)};
            SDL_Rect src{(TILE_SIZE+2*TEXTURE_TO_GAME)*texture, 0, TILE_SIZE+2*TEXTURE_TO_GAME, TILE_SIZE+2*TEXTURE_TO_GAME};
            SDL_Rect dst{j*TILE_SIZE-1*TEXTURE_TO_GAME, (i-fract_part)*TILE_SIZE-1*TEXTURE_TO_GAME, TILE_SIZE+2*TEXTURE_TO_GAME, TILE_SIZE+2*TEXTURE_TO_GAME};
            int code = image.render(&src, &dst);
            if (code!=0)
            { 
                error = code;
            }
        }
    }
    return error;
}