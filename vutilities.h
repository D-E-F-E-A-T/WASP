#ifndef VUTILITIES_H
#define VUTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif

#define FREEIT(ptr) {free(ptr);ptr=NULL;}
    
char* get_file_contents(const char* path);
int get_file_contents_binary(char* out_bytes, const char* path);

#ifdef __cplusplus
}
#endif

#endif /* VUTILITIES_H */

