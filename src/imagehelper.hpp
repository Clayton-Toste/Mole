#pragma once

#include "object.hpp"

#define FONT "assets/sans.ttf"

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

class MoleApp;

class ImageHelper : public Object
{

public:
    ImageHelper(MoleApp *const app, const char *const image = nullptr);
    ~ImageHelper();

    int render(const SDL_Rect *const srcrect = NULL, SDL_Rect *const dstrect = NULL) const;
    bool setImage(const char *const image);
    bool setText(const char *const text, const unsigned char size = 24);

    const SDL_Surface *const getImage() const;

private:
    SDL_Surface *image;
};

#include "main.hpp"