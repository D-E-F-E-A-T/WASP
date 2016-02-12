
#include "glad.h"
#include <GLFW/glfw3.h>


void errcheck() {
    int err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("err");
        switch (err) {
            case GL_INVALID_ENUM: printf("GL_INVALID_ENUM");
                break;
            case GL_INVALID_VALUE: printf("GL_INVALID_VALUE");
                break;
            case GL_INVALID_OPERATION: printf("GL_INVALID_OPERATION");
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: printf("GL_INVALID_FRAMEBUFFER_OPERATION");
                break;
            case GL_OUT_OF_MEMORY: printf("GL_OUT_OF_MEMORY");
                break;
            case GL_STACK_UNDERFLOW: printf("GL_STACK_UNDERFLOW");
                break;
            case GL_STACK_OVERFLOW: printf("GL_STACK_OVERFLOW");
                break;
        }
    }
}

#include "shader_loader.h"
#include "mesh_loader.h"
#include "vutilities.h"

int main(void) {

    GLFWwindow* window;

    glfwWindowHint(GLFW_SAMPLES, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!glfwInit()) {
        printf("Something went wrong!\n");
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        printf("Something went wrong!\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        printf("Something went wrong!\n");
        exit(-1);
    }

    GLuint testprogram;
    int result = compile_program_vf(&testprogram, "shader.vs", "shader.fs");
    errcheck();
    printf("compiled");

    float post_processing_vbo[] = {
        -1.0, -1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        1.0, -1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0,
        -1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0,
        -1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0,
        1.0, -1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0
    };
    
    char* teapot_bytes;
    int teapotbc = get_file_contents_binary(&teapot_bytes, "teapot.vbo");
    int teapot_floats = teapotbc / 4;
    int teapot_vertices = teapot_floats / 8;
    float* teapot_float_array = (float*)teapot_bytes;
   // for(int x=0;x<teapot_floats;x++){
  //      printf("%d: %f\n", x, *(teapot_float_array+x));
  //  }
    
    
    struct Mesh post_processing_mesh;
    create_drawable(&post_processing_mesh, teapot_vertices, teapot_float_array);
    errcheck();
    printf("mesh created");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(1, 0, 0, 1);
    glClearDepth(1);
    glViewport(0, 0, 640, 480);
    glUseProgram(testprogram);
    int timeloc = glGetUniformLocation(testprogram, "Time");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float time = (float)glfwGetTime();

        glUseProgram(testprogram);
        glUniform1f(timeloc, time);
        draw_vao(post_processing_mesh);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}