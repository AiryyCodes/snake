#pragma once

#include <stdint.h>
#include <math.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;

typedef u8 bool;
#define true 1
#define false 0

typedef struct
{
    i16 x;
    i16 y;
} ivec2;

typedef struct
{
    f32 x;
    f32 y;
} fvec2;

typedef struct
{
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} fvec4;

typedef struct
{
    fvec4 column[4];
} mat4;

typedef struct
{
    float r;
    float g;
    float b;
    float a;
} Color;

void mat4_identity(mat4 *matrix);

void mat4_translate(mat4 *matrix, fvec2 vector);
void mat4_scale(mat4 *matrix, float scale);

void convert_mat4(const mat4 *matrix, float out[16]);

static bool float_equals(float a, float b)
{
    return fabs(a - b) < 0.0001f;
}
