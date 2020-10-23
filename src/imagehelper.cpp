#include "imagehelper.hpp"

ImageHelper::ImageHelper(MoleApp *const app) : Object(app){ }

ImageHelper::ImageHelper(MoleApp *const app, const char *const name) : Object(app)
{
    if (name == nullptr)
    {
        return;
    }
    if (!setImage(name))
    {
        std::cout << "Failed to create image " << name << ".\n";
    }
}

ImageHelper::ImageHelper(MoleApp *const app, const char *const text, const unsigned char size) : Object(app)
{
    if (text == nullptr)
    {
        return;
    }
    if (!setText(text, size))
    {
        std::cout << "Failed to create text " << text << ".\n";
    }
}

ImageHelper::~ImageHelper()
{
    if (image)
    {
        SDL_FreeSurface(image);
    }
}

int ImageHelper::render(const SDL_Rect *srcrect, SDL_Rect *dstrect) const
{
    return SDL_BlitSurface(image, srcrect, app->surface, dstrect);
}

bool ImageHelper::setImage(const char *name)
{
    if (
        name == nullptr ||
        (image = IMG_Load(name)) == NULL)
    {
        return false;
    }
    return true;
}

bool ImageHelper::setText(const char *text, unsigned char size)
{
    TTF_Font *font = TTF_OpenFont(FONT, size);

    if (
        text == nullptr ||
        font == nullptr ||
        (image = TTF_RenderText_Solid(font, text, SDL_Color{0, 0, 0})) == NULL)
    {
        TTF_CloseFont(font);
        return false;
    }
    TTF_CloseFont(font);
    return true;
}

const SDL_Surface *const ImageHelper::getImage() const
{
    return image;
};