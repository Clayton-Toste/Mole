#include "main.hpp"

MoleApp::MoleApp() {
}
 
int MoleApp::execute() {
    if(!onInit()) 
    {
        std::cout<<"Init failed.\n";
        return -1;
    }
 
    SDL_Event event;
 
    while(Running) 
    {
        while(SDL_PollEvent(&event)) 
        {
            onEvent(&event);
        }
 
        onUpdate();
        onRender();
    }
 
    onCleanup();
 
    return 0;
}
 
bool MoleApp::onInit()
{
    //Intilize window and renderer
    int flags = IMG_INIT_PNG;
    if (
        SDL_Init(SDL_INIT_EVERYTHING) < 0 ||
        !(IMG_Init(flags) & flags) ||
        (display = SDL_CreateWindow("Mole Game", 
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT,
                                    SDL_WINDOW_OPENGL)) == NULL ||
        (surface = SDL_GetWindowSurface( display )) == NULL
    )
    {
        return false;
    }

    ADD_RENDER_OBJECT(new Background(this))
    ADD_RENDER_OBJECT(new Dirt(this))
    
    for (int i=0; i<LOADED_TILES; i++)
    {
        tiles[i] = perlin::row(i);
    }

    previousTime = std::chrono::high_resolution_clock::now();
    return true;
}

void MoleApp::onEvent( const SDL_Event * const event ) 
{
    if(event->type == SDL_QUIT)
    {
        Running = false;
    }
}

void MoleApp::onUpdate() 
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = (currentTime - previousTime).count();
    previousTime = currentTime;
    scroll+=deltaTime/1000000000.0;
}
 
void MoleApp::onRender()
{
    int failed {0};
    int code;
    for (auto renderable : renderables)
    {
        if ((code = renderable->render()) != 0)
        {
            std::cout<<"Failed to render with error: "<<SDL_GetError()<<'\n';
            ++failed;
        }
    }
    if (failed)
    {
        std::cout<<"Failed to render "<<failed<<" objects.\n";
    }
    SDL_UpdateWindowSurface( display );
}
 
void MoleApp::onCleanup()
{
    for (auto obj : objects)
    {
        delete obj;
    }
}

int main( int argc, char* argv[] )
{
    MoleApp app;
 
    return app.execute();
}