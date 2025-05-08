#pragma once

#include "base.h"
#include "mesh.h"
#include "shader.h"
// #include "snake.h"

static fvec2 FOOD_VERTICES[] = {
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
    bool placed;

    fvec2 position;

    Mesh *mesh;
} Food;

void food_render(const Food *food, Shader *shader);

void food_place(ivec2 position, Food *food);
// void food_eat(Food **food, const Snake *snake);
