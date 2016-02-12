#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#ifdef __cplusplus
extern "C" {
#endif

int compile_program_vf(GLuint *out_program, const GLchar *vertex_file, const GLchar *fragment_file);

#ifdef __cplusplus
}
#endif

#endif /* SHADER_LOADER_H */

