#include "shader.h"
#include "base.h"
#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>

void shader_bind(Shader *shader)
{
    if (!shader)
        return;

    glUseProgram(shader->id);
}

void shader_unbind(Shader *shader)
{
    glUseProgram(0);
}

void shader_set_mat4(Shader *shader, const char *name, mat4 value)
{
    int location = glGetUniformLocation(shader->id, name);
    float matrix[16];
    convert_mat4(&value, matrix);

    glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void shader_set_color(Shader *shader, const char *name, Color color)
{
    int location = glGetUniformLocation(shader->id, name);
    float vector[4] = {
        color.r,
        color.g,
        color.b,
        color.a,
    };

    glUniform4fv(location, 1, vector);
}

u32 compile_shader(const char *path, const char *name, u32 type)
{
    File *file = file_open(path, "r");
    if (!file)
    {
        printf("Failed to open shader file '%s'\n", path);
        return 0;
    }

    u32 shader_id = glCreateShader(type);

    const char *source = file_read_all(file);
    glShaderSource(shader_id, 1, &source, NULL);
    glCompileShader(shader_id);

    int status;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);

    if (!status)
    {
        char log[512] = "";
        glGetShaderInfoLog(shader_id, 512, NULL, log);

        printf("Failed to compile %s shader.\n%s", name, log);

        return 0;
    }

    return shader_id;
}

Shader *shader_create(const char *vertex_path, const char *fragment_path)
{
    u32 vertex_shader = compile_shader(vertex_path, "vertex", GL_VERTEX_SHADER);
    if (!vertex_shader)
    {
        return NULL;
    }

    u32 fragment_shader = compile_shader(fragment_path, "fragment", GL_FRAGMENT_SHADER);
    if (!fragment_shader)
    {
        return NULL;
    }

    u32 id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);
    glLinkProgram(id);

    int status;
    glGetShaderiv(id, GL_LINK_STATUS, &status);

    if (!status)
    {
        char log[512] = "";
        glGetProgramInfoLog(id, 512, NULL, log);

        printf("Failed to link shader program.\n%s", log);

        return NULL;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    Shader *shader = malloc(sizeof(Shader));
    shader->id = id;

    return shader;
}
