#pragma once

#include "base.h"
#include "food.h"
#include "mesh.h"
#include "shader.h"

#define MAX_SNAKE_LENGTH 100

static fvec2 SNAKE_VERTICES[] = {
    // Bottom Triangle
    {-1.0f, -1.0f},
    {1.0f, -1.0f},
    {1.0f, 1.0f},
    // Top Triangle
    {-1.0f, -1.0f},
    {-1.0f, 1.0f},
    {1.0f, 1.0f},
};

typedef struct
{
    fvec2 position;
    fvec2 last_position;

    Mesh *mesh;
} SnakeSegment;

typedef struct
{
    ivec2 direction;

    i32 length;
    SnakeSegment body[MAX_SNAKE_LENGTH];
} Snake;

void snake_eat(Food *food, Snake *snake);
void snake_reset(Snake *snake);

void snake_update(Snake *snake);
void snake_render(Snake *snake, Shader *shader);
void snake_init(Snake *snake);
