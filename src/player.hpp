#pragma once

#include "object.hpp"
#include "components.hpp"
#include "imagehelper.hpp"

#define ANIMATION_SPEED_STILL 3
#define ANIMATION_SPEED_MOVE 5
#define ANIMATION_SPEED_DIG  ANIMATION_SPEED_MOVE
#define ANIMATION_SPEED_FALL 12

#define MOVE_SPEED 25
#define FALL_SPEED 40
#define DIG_SPEED  MOVE_SPEED

#define DIG_MOVEMENT(n) 2*n*(1-n)

#define TILE_Y(offset) (app->tile_scroll+tile_y+offset)%100
#define TILE_X(offset) 1<<(tile_x+offset)
#define TILE_AT(x_offset, y_offset) bool(app->tiles[TILE_Y(y_offset)] & TILE_X(x_offset))

#define PLAYER_DEPTH 5

#include <cmath>
#include <math.h>
#include <limits>

class MoleApp;

class Player: public RenderComponent, public UpdateComponent, public Object
{
public:
    Player( MoleApp * const app );
    ~Player( ) { };

    enum action
    {
        move_down, 
        move_left, 
        move_up, 
        move_right,
        no_action
    } current_action {no_action};
    
    void dig( );

    const int render( ) const override;
    const int update( ) override;

private:

    enum state 
    {
        still_down, 
        still_left, 
        still_up, 
        still_right, 
        falling, 
        moving_left=6, 
        moving_right=8,
        diging_down=10, 
        diging_left, 
        diging_up, 
        diging_right,
    } current_state {falling};

    void updateAction( );
    void endAction( const state end );

    signed int frame {0};
    unsigned int movement;
    float x {0}, y {PLAYER_DEPTH};
    int tile_x {0}, tile_y {PLAYER_DEPTH};

    const ImageHelper image;

};