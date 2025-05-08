#include "food.h"
#include "base.h"
#include "game.h"
#include "mesh.h"
#include "shader.h"

#include <stdlib.h>
#include <time.h>

void food_render(const Food *food, Shader *shader)
{
    if (!food->placed || food->mesh == NULL)
        return;

    mat4 transform;
    mat4_identity(&transform);
    mat4_translate(&transform, food->position);
    mat4_scale(&transform, 0.05f);

    shader_set_mat4(shader, "u_Transform", transform);
    shader_set_color(shader, "u_Color", (Color){1.0f, 0.0f, 0.0f, 1.0f});

    mesh_draw(food->mesh);
}

void food_place(ivec2 position, Food *food)
{
    food->placed = true;

    const int min = -WORLD_SIZE;
    const int max = WORLD_SIZE;

    u32 seed = time(0);

    int randomX = rand_r(&seed) % (max - min + 1) + min;
    int randomY = rand_r(&seed) % (max - min + 1) + min;

    food->position.x = randomX * 0.1f;
    food->position.y = randomY * 0.1f;

    /*food->position.x = position.x * 0.1f;*/
    /*food->position.y = position.y * 0.1f;*/

    food->mesh = mesh_create(FOOD_VERTICES, 6);
}
