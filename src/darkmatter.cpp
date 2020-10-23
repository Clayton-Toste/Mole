#include "darkmatter.hpp"

DarkMatter::DarkMatter(MoleApp *const app) : image{app, "assets/dark_matter.png"}, Object{app} {}

void DarkMatter::addEnemy()
{
    int angle{rand()};
    float c{cos(angle)}, s{sin(angle)};
    if (abs(c) > abs(s))
    {
        std::cout << c << ',' << s << std::endl;
        enemies.emplace_back(Enemy{
            rand() % SPAWN_RANGE + TOP_PADDING + app->scroll,
            c,
            s});
    }
    else
    {
        std::cout << s << ',' << c << std::endl;
        enemies.emplace_back(Enemy{
            rand() % SPAWN_RANGE + TOP_PADDING + app->scroll,
            s,
            -c});
    }
}

const int DarkMatter::update()
{
    enemies.remove_if([this](Enemy &enemy) -> bool {
        // Update locations
        if (enemy.life > std::numeric_limits<unsigned int>::max() - app->deltaTime)
        {
            //return true;
        }

        enemy.life += app->deltaTime * ENEMY_SPEED;

        double distance = ((double)(ENEMY_PATH_LENGTH * enemy.life) / std::numeric_limits<unsigned int>::max() - (ENEMY_WIDTH / 2.0 + 100));
        float flux = sin((int)distance / (float)ENEMY_FLUX_PERIOD * 2.0 * M_PI) * ENEMY_FLUX_STENGTH;
        enemy.currX = distance * enemy.deltaX - flux * enemy.deltaY;
        enemy.currY = distance * enemy.deltaY + flux * enemy.deltaX;

        if (enemy.deltaX < 0)
        {
            enemy.currX += SCREEN_WIDTH;
        }

        // Check for collision with player
        if ((ENEMY_CENTER_RADIUS + PLAYER_CENTER_RADIUS) * (ENEMY_CENTER_RADIUS + PLAYER_CENTER_RADIUS) > pow(enemy.currX - app->player->x * TILE_SIZE - PLAYER_CENTER_WIDTH, 2) + pow(enemy.currY + enemy.y - (app->player->y + app->scroll) * TILE_SIZE - PLAYER_CENTER_HEIGHT, 2))
        {
            std::cout << "game end" << std::endl;
        }

        return false;
    });
    return 0;
}

const int DarkMatter::render() const
{
    int error, code, texture;
    SDL_Rect src, dst;

    for (auto enemy : enemies)
    {
        texture = (enemy.life % ENEMY_ANIMATION_FRAMES_LENGTH) / ENEMY_ANIMATION_FRAME_LENGTH;

        src = SDL_Rect{texture * ENEMY_WIDTH, 0, ENEMY_WIDTH, ENEMY_HEIGHT};
        dst = SDL_Rect{enemy.currX - ENEMY_CENTER_WIDTH, enemy.currY + enemy.y - app->scroll * TILE_SIZE - ENEMY_CENTER_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT};

        code = image.render(&src, &dst);

        if (!code)
        {
            error = code;
        }
    }
    return error;
}