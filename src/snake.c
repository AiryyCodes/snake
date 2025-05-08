#include "snake.h"
#include "base.h"
#include "game.h"
#include "mesh.h"
#include "shader.h"
#include <stdio.h>
#include <stdlib.h>

void update_body(Snake *snake, fvec2 new_position)
{
    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->body[i].last_position = snake->body[i].position;
        snake->body[i] = snake->body[i - 1];
    }

    snake->body[0].last_position = snake->body[0].position;
    snake->body[0].position = new_position;
}

void snake_update(Snake *snake)
{
    fvec2 position = snake->body[0].position;
    position.x += snake->direction.x * 0.1f;
    position.y += snake->direction.y * 0.1f;
    update_body(snake, position);

    for (int i = 1; i < snake->length - 1; i++)
    {
        SnakeSegment body = snake->body[i];

        if (float_equals(position.x, body.position.x) && float_equals(position.y, body.position.y))
        {
            game_reset();
        }
    }
}

void snake_render(Snake *snake, Shader *shader)
{
    for (int i = 0; i < snake->length; i++)
    {
        SnakeSegment *segment = &snake->body[i];
        if (!segment->mesh)
            continue;

        mat4 transform;
        mat4_identity(&transform);
        mat4_translate(&transform, segment->position);
        mat4_scale(&transform, 0.05f);

        shader_set_mat4(shader, "u_Transform", transform);
        shader_set_color(shader, "u_Color", (Color){1.0f, 1.0f, 1.0f, 1.0f});

        mesh_draw(segment->mesh);
    }
}

void snake_eat(Food *food, Snake *snake)
{
    snake->length++;

    // The last snake segment's position is 0, 0 so i set it to the next last position
    snake->body[snake->length - 1].position = snake->body[snake->length - 2].position;

    food->placed = false;
}

void snake_reset(Snake *snake)
{
    for (int i = 0; i < snake->length; i++)
    {
        snake->body[i].position = (fvec2){0, 0};
    }

    snake->length = 3;
    snake->direction = (ivec2){0, 0};
}

void snake_init(Snake *snake)
{
    snake->direction = (ivec2){0, 0};

    snake->length = 3;
    snake->body[0].position = (fvec2){0, 0};
    snake->body[0].mesh = mesh_create(SNAKE_VERTICES, 6);
    /*snake->body[1].position = (fvec2){0.1f, 0};*/
    /*snake->body[1].mesh = mesh_create(SNAKE_VERTICES, 6);*/
    /*snake->body[2].position = (fvec2){0.2f, 0};*/
    /*snake->body[2].mesh = mesh_create(SNAKE_VERTICES, 6);*/
}
