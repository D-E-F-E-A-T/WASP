#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <windows.h>

static int fsize(FILE* fh) {
    int prev = ftell(fh);
    fseek(fh, 0L, SEEK_END);
    int sz = ftell(fh);
    fseek(fh, prev, SEEK_SET);
    return sz;
}

char* get_file_contents(const char* path) {
    FILE* fh = fopen(path, "r");
    int size = fsize(fh);
    char* content = calloc(size + 1, sizeof (char));
    int sz = fread(content, sizeof (char), size, fh);
    content = realloc(content, sizeof (char) * sz + 1);
    content[sz] = 0;
    fclose(fh);
    return content;
}

int get_file_contents_binary(char** out_bytes, const char* path) {
    FILE* fh = fopen(path, "rb");
    int size = fsize(fh);
    char* content = calloc(size, 1);
    int sz = fread(content, 1, size, fh);
    fclose(fh);
    *out_bytes = content;
    return size;
}