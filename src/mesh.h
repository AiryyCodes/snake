#pragma once

#include "base.h"

typedef struct
{
    u32 id;
    i32 num_vertices;
} Mesh;

void mesh_draw(Mesh *mesh);
Mesh *mesh_create(fvec2 vertices[], int num_vertices);
