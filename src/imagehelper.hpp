#pragma once

#include "object.hpp"

#include <SDL.h>

#include <string>

class MoleApp;

class ImageHelper : public Object
{

public:
    ImageHelper( MoleApp * const app, const char * const image=nullptr );
    ~ImageHelper( );

    int render( const SDL_Rect * const srcrect=NULL, SDL_Rect * const dstrect=NULL ) const;
    bool setImage( const char * const image );

private:
    SDL_Surface * image;

};

#include "main.hpp"