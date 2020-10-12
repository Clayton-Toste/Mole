#pragma once

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 400
#define LOADED_TILES 100
#define TILE_SIZE 50
#define TEXTURE_TO_GAME 5
#define GAME_TO_TEXTURE 1/TEXTURE_TO_GAME
#define TEXTURE_TO_TILE TILE_SIZE*GAME_TO_TEXTURE
#define TILE_HEIGHT SCREEN_HEIGHT/TILE_SIZE
#define TILE_WIDTH SCREEN_WIDTH/TILE_SIZE


#define ADD_RENDER(object) objects.push_back(reinterpret_cast<void *>(object));
#define ADD_OBJECT(object) renderables.push_back(object);
#define ADD_RENDER_OBJECT(object) ADD_RENDER(object) ADD_OBJECT(object)

#include "object.hpp"
#include "rendercomponent.hpp"
#include "dirt.hpp"
#include "bg.hpp"
#include "perlin.hpp"

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <chrono>
#include <list>

class MoleApp
{
 
private:
    bool onInit();
    void onEvent( const SDL_Event * const event );
    void onUpdate();
    void onRender();
    void onCleanup();


    void pushBackDirtRow();
    void pushFrontDirtRow();

    bool Running{true};

    std::chrono::_V2::system_clock::time_point previousTime;

public:
    MoleApp();

    int execute();

    std::list<void *> objects = {};
    std::list<RenderComponent *> renderables = {};

    SDL_Window * display;
    SDL_Surface * surface;

    unsigned int tiles[LOADED_TILES]={};

    long double scroll{0};
    int offset;

    time_t deltaTime;

};