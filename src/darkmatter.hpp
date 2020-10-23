#pragma once

#include "object.hpp"
#include "components.hpp"
#include "imagehelper.hpp"

#define TOP_PADDING 200
#define BOTTOM_PADDING -200
#define SPAWN_RANGE (SCREEN_HEIGHT - (TOP_PADDING + BOTTOM_PADDING))
#define ENEMY_WIDTH 60
#define ENEMY_HEIGHT 100
#define ENEMY_SPEED 1
#define ENEMY_SPAWN_RATE .3
#define ENEMY_FLUX_STENGTH 10
#define ENEMY_FLUX_PERIOD 200
#define ENEMY_ANIMATION_SPEED 6
#define ENEMY_ANIMATION_FRANES 7
#define ENEMY_ANIMATION_FRAMES_LENGTH (int)(std::numeric_limits<unsigned int>::max() / (ENEMY_ANIMATION_SPEED))
#define ENEMY_ANIMATION_FRAME_LENGTH (int)(std::numeric_limits<unsigned int>::max() / (ENEMY_ANIMATION_FRANES * ENEMY_ANIMATION_SPEED))
#define ENEMY_CENTER_WIDTH ENEMY_WIDTH / 2
#define ENEMY_CENTER_HEIGHT ENEMY_HEIGHT * 3 / 4
#define ENEMY_CENTER_RADIUS ENEMY_WIDTH / 2
#define ENEMY_PATH_LENGTH (SCREEN_WIDTH + 2*ENEMY_WIDTH) * M_SQRT2

#include <cstdlib>
#include <algorithm>

class MoleApp;

class DarkMatter : public RenderComponent, public UpdateComponent, public Object
{
public:
    DarkMatter(MoleApp *const app);
    ~DarkMatter(){};

    void addEnemy();

    const int update() override;
    const int render() const override;

private:
    struct Enemy
    {
        const long double y;
        const float deltaX, deltaY;
        unsigned int life = 0;
        double currX = 0, currY = 0;
    };
    std::list<Enemy> enemies{};
    const ImageHelper image;
};