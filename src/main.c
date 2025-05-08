#include "renderer.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#define TARGET_FPS 8

int main(void)
{
    Renderer renderer;
    renderer_init(&renderer);

    game_init();

    double current_time = glfwGetTime();
    double last_time = current_time;
    double time_behind = 0.0;
    while (!glfwWindowShouldClose(renderer.window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        current_time = glfwGetTime();
        if (current_time - last_time >= 1.0 / TARGET_FPS)
        {
            last_time = current_time;
            game_update();
        }

        game_render();

        glfwPollEvents();
        glfwSwapBuffers(renderer.window);
    }

    return EXIT_SUCCESS;
}
