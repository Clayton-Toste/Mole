#pragma once

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 400
#define LOADED_TILES 100
#define TILE_SIZE 50
#define TILE_HEIGHT SCREEN_HEIGHT/TILE_SIZE
#define TILE_WIDTH SCREEN_WIDTH/TILE_SIZE
#define TEXTURE_PIXEL 5
#define TILE_TEXTURE_SIZE (TILE_SIZE + 2*TEXTURE_PIXEL)

#define ADD_RENDER(object) renderables.push_back(object);
#define ADD_UPDATE(object) updateables.push_back(object);
#define ADD_OBJECT(object) objects.push_back(object);
#define ADD_RENDER_OBJECT(object) ADD_RENDER(object) ADD_OBJECT(object)
#define ADD_RENDER_UPDATE_OBJECT(object) ADD_UPDATE(object) ADD_RENDER_OBJECT(object)

#include <SDL.h>
#include <SDL_image.h>

#include "object.hpp"
#include "components.hpp"

#include <iostream>
#include <chrono>
#include <list>

class Player;

class MoleApp
{
 
private:
    bool onInit();
    void onEvent( const SDL_Event * const event );
    void onUpdate();
    void onRender();
    void onCleanup();

    void pushFrontDirtRow();

    bool Running{true};

    std::chrono::_V2::system_clock::time_point previousTime;

    std::list<Object *> objects = {};
    std::list<RenderComponent *> renderables = {};
    std::list<UpdateComponent *> updateables = {};

public:
    MoleApp();

    int execute();

    SDL_Window * display;
    SDL_Surface * surface;

    unsigned int tiles[LOADED_TILES]={};

    long double scroll{0};
    unsigned long int tile_scroll{0};
    int offset;

    Player * player;

    time_t deltaTime;

};

#include "dirt.hpp"
#include "bg.hpp"
#include "player.hpp"
#include "perlin.hpp"
