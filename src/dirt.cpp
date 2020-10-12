#include "dirt.hpp"

#include <SDL.h>

Dirt::Dirt(MoleApp * const app) : image{app, "dirt.bmp"}, Object{app}
{

}

int Dirt::render() const 
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
            SDL_Rect src{0, TILE_SIZE*GAME_TO_TEXTURE*TEXTURE_HASH(i+(int)app->scroll, j), TILE_SIZE*GAME_TO_TEXTURE, TILE_SIZE*GAME_TO_TEXTURE};
            SDL_Rect dst{j*TILE_SIZE, (i-fract_part)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            int code = image.render(&src, &dst);
            if (code!=0)
            { 
                error = code;
            }
        }
    }
    return error;
}