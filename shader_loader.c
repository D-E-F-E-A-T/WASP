#include "glad.h"
#include "vutilities.h"

/* PRIVATE */


static int compile_shader(GLuint *out_shader, GLenum type, const GLchar *source) {
    GLuint shader = glCreateShader(type);
    printf("%s", source);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != 1) {
        GLint loglen;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &loglen);
        char* log = calloc(loglen + 1, sizeof (char));
        glGetShaderInfoLog(shader, loglen, NULL, log);
        printf("COMPILATION FAILED WITH MESSAGE::\n%s", log);
        FREEIT(log);
    }
    *out_shader = shader;
    return status;
}

/* PUBLIC */

int compile_program_vf(GLuint *out_program, const GLchar *vertex_file, const GLchar *fragment_file) {
    char* vshadersrc = get_file_contents(vertex_file);
    char* fshadersrc = get_file_contents(fragment_file);
    GLuint vshader, fshader, program;
    int result = 1;
    result *= compile_shader(&vshader, GL_VERTEX_SHADER, vshadersrc);
    result *= compile_shader(&fshader, GL_FRAGMENT_SHADER, fshadersrc);
    program = glCreateProgram();
    glAttachShader(program, vshader);
    glAttachShader(program, fshader);
    glLinkProgram(program);
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status != 1) {
        GLint loglen;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &loglen);
        char* log = calloc(loglen + 1, sizeof (char));
        glGetProgramInfoLog(program, loglen, NULL, log);
        printf("LINKING FAILED WITH MESSAGE::\n%s", log);
        FREEIT(log);
    }
    result *= status;
    *out_program = program;
    return result;
}

