#pragma once

#include "base.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

typedef struct
{
    GLFWwindow *window;
} Renderer;

bool renderer_init(Renderer *renderer);
void renderer_destroy(Renderer *renderer);
