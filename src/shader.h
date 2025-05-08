#pragma once

#include "base.h"

typedef struct
{
    u32 id;
} Shader;

void shader_bind(Shader *shader);
void shader_unbind(Shader *shader);

void shader_set_mat4(Shader *shader, const char *name, mat4 value);
void shader_set_color(Shader *shader, const char *name, Color color);

Shader *shader_create(const char *vertex_path, const char *fragment_path);
