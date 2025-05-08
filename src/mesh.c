#include "mesh.h"
#include "base.h"

#include <glad/gl.h>
#include <stdlib.h>

void mesh_draw(Mesh *mesh)
{
    glBindVertexArray(mesh->id);
    glDrawArrays(GL_TRIANGLES, 0, mesh->num_vertices);
}

Mesh *mesh_create(fvec2 vertices[], int num_vertices)
{
    u32 vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    u32 vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(fvec2), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Mesh *mesh = malloc(sizeof(Mesh));
    mesh->id = vao;
    mesh->num_vertices = num_vertices;

    return mesh;
}
