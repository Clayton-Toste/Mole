#include "bg.hpp"


Background::Background(MoleApp * const app) : image{app, "assets/bg.png"}, Object{app} {}

const int Background::render() const 
{
    int code {0};
    SDL_Rect src;
    SDL_Rect dst;
    src = SDL_Rect {SCREEN_WIDTH, 0, SCREEN_WIDTH, int(app->scroll*TILE_SIZE*BACKGROUND_SCROLL) % SCREEN_HEIGHT};
    dst = SDL_Rect {0, SCREEN_HEIGHT-src.h, SCREEN_WIDTH, src.h};
    code |= image.render(&src, &dst);
    src = SDL_Rect {SCREEN_WIDTH, src.h, SCREEN_WIDTH, SCREEN_HEIGHT-src.h};
    dst = SDL_Rect {0, 0, SCREEN_WIDTH, src.h};
    code |= image.render(&src, &dst);
    src = SDL_Rect {0, 0, SCREEN_WIDTH, int(app->scroll*TILE_SIZE*FOREGROUND_SCROLL) % SCREEN_HEIGHT};
    dst = SDL_Rect {0, SCREEN_HEIGHT-src.h, SCREEN_WIDTH, src.h};
    code |= image.render(&src, &dst);
    src = SDL_Rect {0, src.h, SCREEN_WIDTH, SCREEN_HEIGHT-src.h};
    dst = SDL_Rect {0, 0, SCREEN_WIDTH, src.h};
    code |= image.render(&src, &dst);
    return code;
}