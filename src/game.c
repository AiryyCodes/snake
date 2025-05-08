#include "game.h"
#include "base.h"
#include "food.h"
#include "shader.h"
#include "snake.h"

#include <stdio.h>

static Game game;

void game_init()
{
    game.shader = shader_create("shaders/main.vert", "shaders/main.frag");

    game.has_started = false;
    snake_init(&game.snake);
}

void game_update()
{
    if (!game.has_started)
        return;

    snake_update(&game.snake);
    SnakeSegment snake_head = game.snake.body[0];

    // Out of bounds check
    if (snake_head.position.x > 9 * 0.1f || snake_head.position.x < -(10 * 0.1f) ||
        snake_head.position.y > 10 * 0.1f || snake_head.position.y < -(10 * 0.1f))
    {
        game_reset();
        return;
    }

    // printf("Snake: X: %f Y: %f\n", snake_head.position.x, snake_head.position.y);

    if (!game.food.placed)
    {
        return;
    }

    if (float_equals(snake_head.position.x, game.food.position.x) && float_equals(snake_head.position.y, game.food.position.y))
    {
        snake_eat(&game.food, &game.snake);

        food_place((ivec2){0, 0}, &game.food);
    }
}

void game_render()
{
    if (!game.has_started)
        return;

    shader_bind(game.shader);
    snake_render(&game.snake, game.shader);
    food_render(&game.food, game.shader);
}

void game_reset()
{
    game.has_started = false;
    snake_reset(&game.snake);
    game.food.placed = false;
}

Game *get_game()
{
    return &game;
}

void input_handler(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    if (key == GLFW_KEY_SPACE)
    {
        game.snake.direction.x = -1;
        game.snake.direction.y = 0;
        game.has_started = true;
        food_place((ivec2){0, 0}, &game.food);
    }

    if (key == GLFW_KEY_P && !game.food.placed)
    {
        food_place((ivec2){2, 0}, &game.food);
        printf("Food: X: %f Y: %f\n", game.food.position.x, game.food.position.y);
    }

    ivec2 direction = {0, 0};
    if (key == GLFW_KEY_W && game.snake.direction.y != -1)
    {
        direction.y = 1;
    }
    else if (key == GLFW_KEY_S && game.snake.direction.y != 1)
    {
        direction.y = -1;
    }
    else if (key == GLFW_KEY_A && game.snake.direction.x != 1)
    {
        direction.x = -1;
    }
    else if (key == GLFW_KEY_D && game.snake.direction.x != -1)
    {
        direction.x = 1;
    }

    if (direction.x != 0 || direction.y != 0)
    {
        game.snake.direction = direction;
    }
}
