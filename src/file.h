#pragma once

#include <stdio.h>

typedef struct
{
    FILE *file;
    const char *path;
} File;

File *file_open(const char *path, const char *mode);
void file_close(File *file);

char *file_read_all(File *file);
