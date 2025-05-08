#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

File *file_open(const char *path, const char *mode)
{
    File *myFile = malloc(sizeof(File));
    if (!myFile)
    {
        // Failed to create instance of file
        return NULL;
    }

    FILE *file = fopen(path, mode);
    if (!file)
    {
        printf("Failed to open file '%s'.\n", path);
        return NULL;
    }

    myFile->file = file;
    myFile->path = path;

    return myFile;
}

void file_close(File *file)
{
    if (!file)
        return;

    fclose(file->file);
}

char *file_read_all(File *file)
{
    struct stat statbuf;
    int status = stat(file->path, &statbuf);
    if (status == -1)
    {
        return "";
    }

    int fileSize = statbuf.st_size;
    char *content = malloc(fileSize);

    int index = 0;
    int c;
    while ((c = fgetc(file->file)) != EOF)
    {
        content[index++] = (char)c;
    }

    content[index] = '\0';

    return content;
}
