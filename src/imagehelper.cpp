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

int ImageHelper::render(const SDL_Rect * srcrect, SDL_Rect * dstrect) const
{
    return SDL_BlitSurface(image, srcrect, app->surface, dstrect);
}

bool ImageHelper::setImage( const char * name )
{
    if (
        name == nullptr ||
        app->surface == nullptr ||
        (image = IMG_Load(name)) == NULL
    )
    {
        return false;
    }
    return true;
}