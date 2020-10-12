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
    if (
        SDL_Init(SDL_INIT_EVERYTHING) < 0 ||
        (display = SDL_CreateWindow("Mole Game", 
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT,
                                    SDL_WINDOW_OPENGL)) == NULL ||
        (renderer = SDL_CreateRenderer(display,
                                       -1, 0)) == NULL
    )
    {
        return false;
    }

    Dirt * dirt = new Dirt(this);
    ADD_RENDER_OBJECT(dirt, 1)
    
    for (int i=0; i<LOADED_TILES; i++)
    {
        tiles[i] = perlin::row(i);
        std::cout<<tiles[i]<<std::endl;
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
    for (auto layer : renderables)
    {
        for (auto renderable : layer)
        {
            if (renderable->render() != 0)
            {
                ++failed;
            }
        }
    }
    if (failed)
    {
        std::cout<<"Failed to render "<<failed<<" objects.\n";
    }
    SDL_RenderPresent(renderer);
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