#include "imagehelper.hpp"

ImageHelper::ImageHelper( MoleApp * const app, const char * const name) : Object(app)
{
    if (name == nullptr)
    {
        return ;
    }
    if (!setImage(name))
    {
        std::cout<<"Failed to create image "<<name<<".\n";
    }
}

int ImageHelper::render(const SDL_Rect * srcrect, const SDL_Rect * dstrect) const
{
    return SDL_RenderCopy(app->renderer, texture, srcrect, dstrect);
}

bool ImageHelper::setImage( const char * name )
{
    if (
        name == nullptr ||
        app->renderer == nullptr ||
        (image = SDL_LoadBMP(name)) == NULL ||
        (texture = SDL_CreateTextureFromSurface(app->renderer, image)) == NULL
    )
    {
        return false;
    }
    return true;
}