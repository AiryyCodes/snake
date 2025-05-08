#include "renderer.h"
#include "base.h"
#include "game.h"

#include <stdio.h>

bool renderer_init(Renderer *renderer)
{
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW.\n");
        return false;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Needed on macOS
#endif

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Snake", NULL, NULL);
    if (!window)
    {
        printf("Failed to create GLFW window.\n");
        return false;
    }

    renderer->window = window;

    glfwSetKeyCallback(window, input_handler);

    glfwMakeContextCurrent(window);

    int status = gladLoadGL(glfwGetProcAddress);
    if (!status)
    {
        printf("Failed to initialize OpenGL.\n");
        return false;
    }
    printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(status), GLAD_VERSION_MINOR(status));

    return true;
}

void renderer_destroy(Renderer *renderer)
{
    glfwDestroyWindow(renderer->window);
    glfwTerminate();
}
