#include "player.hpp"

#include <SDL.h>

Player::Player(MoleApp *const app) : image{app, "assets/mole.png"}, Object{app} {}

void Player::dig()
{
    // Check if the player is busy
    if (current_state > 3)
    {
        return;
    }

    // Check if player location is okay for taking action
    switch (current_state)
    {
    case still_down:
        if (!TILE_AT(0, 1))
        {
            return;
        }
        break;
    case still_left:
        if (!TILE_AT(-1, 0))
        {
            return;
        }
        break;
    case still_up:
        if (!TILE_AT(0, -1))
        {
            return;
        }
        break;
    case still_right:
        if (!TILE_AT(1, 0))
        {
            return;
        }
        break;
    }

    // Change state to dig
    current_state = state(current_state + 10);
}

void Player::updateAction()
{
    // Check if the player is busy or if there is nothing to do
    if (current_state > 3 || current_action == no_action)
    {
        return;
    }

    // Turn the player to face correct dirrection
    current_state = (state)current_action;

    // Not allowed to move up and down
    if (current_action == move_up || current_action == move_down)
    {
        return;
    }

    // Check if player would hit a wall
    if (
        (current_state == still_left && (x == 0.0 || TILE_AT(-1, 0))) ||
        (current_state == still_right && (x == 7.0 || TILE_AT(1, 0))))
    {
        return;
    }

    // Change state to move
    current_state = state(current_state + 5);
}

void Player::endAction(const state end)
{
    movement = 0;
    app->collectable->collect();
    if (TILE_AT(0, 1))
    {
        current_state = end;
        return;
    }
    current_state = falling;
}

const int Player::update()
{
    updateAction();

    // Still
    if (current_state < 4)
    {
        frame += app->deltaTime * ANIMATION_SPEED_STILL;
        return 0;
    }

    // Falling
    if (current_state == falling)
    {
        if (movement >= std::numeric_limits<unsigned int>::max() - app->deltaTime * FALL_SPEED)
        {
            app->tile_scroll += 1;
            app->scroll = 0;
            app->addRow();
            endAction(still_down);
            return 0;
        }
        frame += app->deltaTime * ANIMATION_SPEED_FALL;
        movement += FALL_SPEED * app->deltaTime;
        app->scroll = (float)movement / (float)std::numeric_limits<unsigned int>::max();
        return 0;
    }

    // Moving
    if (current_state < 9)
    {
        if (movement >= std::numeric_limits<unsigned int>::max() - app->deltaTime * MOVE_SPEED)
        {
            tile_x += current_state - 7;
            x = tile_x;
            endAction(state(current_state - 5));
            return 0;
        }
        frame += app->deltaTime * ANIMATION_SPEED_MOVE;
        movement += MOVE_SPEED * app->deltaTime;
        x = tile_x + (current_state - 7) * (float)movement / (float)std::numeric_limits<unsigned int>::max();
        return 0;
    }

    // Losing
    if (current_state == lose)
    {
        if (movement >= std::numeric_limits<unsigned int>::max() - app->deltaTime * LOSE_SPEED)
        {
            return 0;
        }
        frame += app->deltaTime * ANIMATION_SPEED_LOSE;
        movement += LOSE_SPEED * app->deltaTime;
        y = tile_y - LOSE_MOVEMENT((float)movement / (float)std::numeric_limits<unsigned int>::max());
        return 0;
    }

    // Digging
    if (movement >= std::numeric_limits<unsigned int>::max() - app->deltaTime * DIG_SPEED)
    {
        x = tile_x;
        y = tile_y;
        switch (current_state)
        {
        case diging_down:
            app->tiles[TILE_Y(1)] ^= TILE_X(0);
            break;
        case diging_left:
            app->tiles[TILE_Y(0)] ^= TILE_X(-1);
            break;
        case diging_up:
            app->tiles[TILE_Y(-1)] ^= TILE_X(0);
            break;
        case diging_right:
            app->tiles[TILE_Y(0)] ^= TILE_X(1);
            break;
        }
        endAction(state(current_state - 10));
    }
    frame += app->deltaTime * ANIMATION_SPEED_DIG;
    movement += DIG_SPEED * app->deltaTime;
    switch (current_state)
    {
    case diging_down:
        y = tile_y + DIG_MOVEMENT((float)movement / (float)std::numeric_limits<unsigned int>::max());
        break;
    case diging_left:
        x = tile_x - DIG_MOVEMENT((float)movement / (float)std::numeric_limits<unsigned int>::max());
        break;
    case diging_up:
        y = tile_y - DIG_MOVEMENT((float)movement / (float)std::numeric_limits<unsigned int>::max());
        break;
    case diging_right:
        x = tile_x + DIG_MOVEMENT((float)movement / (float)std::numeric_limits<unsigned int>::max());
        break;
    }
    return 0;
}

const int Player::render() const
{
    SDL_Rect src{current_state % 5 * TILE_TEXTURE_SIZE, (frame < 0) * TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE};
    SDL_Rect dst{x * TILE_SIZE - 1 * TEXTURE_PIXEL, y * TILE_SIZE - 1 * TEXTURE_PIXEL, TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE};
    return image.render(&src, &dst);
}