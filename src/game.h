#pragma once

#include "base.h"
#include "food.h"
#include "shader.h"
#include "snake.h"
#include <GLFW/glfw3.h>

#define WORLD_SIZE 9

typedef struct
{
    Shader *shader;

    bool has_started;
    Snake snake;
    Food food;
} Game;

void game_init();
void game_update();
void game_render();

void game_reset();

Game *get_game();

void input_handler(GLFWwindow *window, int key, int scancode, int action, int mods);
