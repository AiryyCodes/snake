#include "base.h"

void mat4_identity(mat4 *matrix)
{
    *matrix = (mat4){0};

    matrix->column[0].x = 1.0f;
    matrix->column[1].y = 1.0f;
    matrix->column[2].z = 1.0f;
    matrix->column[3].w = 1.0f;
}

void mat4_translate(mat4 *matrix, fvec2 vector)
{
    matrix->column[3].x += vector.x;
    matrix->column[3].y += vector.y;
}

void mat4_scale(mat4 *matrix, float scale)
{
    matrix->column[0].x = scale;
    matrix->column[1].y = scale;
}

void convert_mat4(const mat4 *matrix, float out[16])
{
    out[0] = matrix->column[0].x;
    out[1] = matrix->column[0].y;
    out[2] = matrix->column[0].z;
    out[3] = matrix->column[0].w;

    out[4] = matrix->column[1].x;
    out[5] = matrix->column[1].y;
    out[6] = matrix->column[1].z;
    out[7] = matrix->column[1].w;

    out[8] = matrix->column[2].x;
    out[9] = matrix->column[2].y;
    out[10] = matrix->column[2].z;
    out[11] = matrix->column[2].w;

    out[12] = matrix->column[3].x;
    out[13] = matrix->column[3].y;
    out[14] = matrix->column[3].z;
    out[15] = matrix->column[3].w;
}
