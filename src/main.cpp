#include "main.hpp"

MoleApp::MoleApp()
{
}

int MoleApp::execute()
{

    if (!onInit())
    {
        std::cout << "Init failed.\n";
        return -1;
    }

    SDL_Event event;

    while (Running)
    {
        while (SDL_PollEvent(&event))
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
    // Initialize SDL
    int flags = IMG_INIT_PNG;
    if (
        SDL_Init(SDL_INIT_EVERYTHING) < 0 ||
        !(IMG_Init(flags) & flags) ||
        TTF_Init() < 0 ||
        (display = SDL_CreateWindow("Mole Game",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT,
                                    SDL_WINDOW_OPENGL)) == NULL ||
        (surface = SDL_GetWindowSurface(display)) == NULL)
    {
        return false;
    }
    
    srand(time(NULL));

    // Construct objects
    background = new Background(this);
    dirt = new Dirt(this);
    player = new Player(this);
    collectable = new Collectable(this);
    darkMatter = new DarkMatter(this);
    hud = new HUD(this);
    ADD_RENDER_OBJECT(background)
    ADD_RENDER_OBJECT(dirt)
    ADD_RENDER_UPDATE_OBJECT(player)
    ADD_RENDER_OBJECT(collectable)
    ADD_RENDER_UPDATE_OBJECT(darkMatter)
    ADD_RENDER_OBJECT(hud)
    for (int i = 0; i< 1; i++)
    {
        darkMatter->addEnemy();
    }
    previousTime = std::chrono::high_resolution_clock::now();

    return true;
}

void MoleApp::onEvent(const SDL_Event *const event)
{
    switch (event->type)
    {
    case SDL_QUIT:
        Running = false;
        return;
    case SDL_KEYDOWN:
        if (event->key.repeat)
        {
            return;
        }
        switch (event->key.keysym.sym)
        {
        case SDLK_w:
        case SDLK_UP:
            player->current_action = Player::move_up;
            break;
        case SDLK_a:
        case SDLK_LEFT:
            player->current_action = Player::move_left;
            break;
        case SDLK_s:
        case SDLK_DOWN:
            player->current_action = Player::move_down;
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            player->current_action = Player::move_right;
            break;
        case SDLK_SPACE:
            player->dig();
        }
        break;
    case SDL_KEYUP:
        switch (event->key.keysym.sym)
        {
        case SDLK_w:
        case SDLK_UP:
            if (player->current_action == Player::move_up)
            {
                player->current_action = Player::no_action;
            }
            break;
        case SDLK_a:
        case SDLK_LEFT:
            if (player->current_action == Player::move_left)
            {
                player->current_action = Player::no_action;
            }
            break;
        case SDLK_s:
        case SDLK_DOWN:
            if (player->current_action == Player::move_down)
            {
                player->current_action = Player::no_action;
            }
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            if (player->current_action == Player::move_right)
            {
                player->current_action = Player::no_action;
            }
            break;
        }
        break;
    }
}

void MoleApp::onUpdate()
{
    // Update deltatime
    auto currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = (currentTime - previousTime).count();
    previousTime = currentTime;

    // Update objects
    int failed{0};
    for (auto updateable : updateables)
    {

        if (updateable->update() != 0)
        {
            std::cout << "Failed to update with error: " << SDL_GetError() << '\n';
            ++failed;
        }
    }
    if (failed)
    {
        std::cout << "Failed to update " << failed << " objects.\n";
    }
}

void MoleApp::onRender()
{
    // Render objects
    int failed{0};
    for (auto renderable : renderables)
    {
        if (renderable->render() != 0)
        {
            std::cout << "Failed to render with error: " << SDL_GetError() << '\n';
            ++failed;
        }
    }
    if (failed)
    {
        std::cout << "Failed to render " << failed << " objects.\n";
    }
    SDL_UpdateWindowSurface(display);
}

void MoleApp::onCleanup()
{
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();

    // Free Memory for Objects
    for (auto obj : objects)
    {
        delete obj;
    }
}

void MoleApp::addRow()
{
    dirt->addRow();
    collectable->addRow();
}

int main(int argc, char *argv[])
{
    MoleApp app;

    return app.execute();
}