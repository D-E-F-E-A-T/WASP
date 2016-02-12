
#include "glad.h"
#include "mesh_loader.h"


int create_drawable(struct Mesh *out_mesh, int vertex_count, GLfloat *floats) {
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * vertex_count * 8, floats, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (GLfloat) * 8, 0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof (GLfloat) * 8, (GLvoid*) (sizeof (GLfloat) * 3));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof (GLfloat) * 8, (GLvoid*) (sizeof (GLfloat) * 5));
    
    glBindVertexArray(0);
    glBindBuffer(0, GL_ARRAY_BUFFER);
    
    struct Mesh mesh;
    mesh.vao = vao;
    mesh.vertex_count = vertex_count;
    *out_mesh = mesh;
    return 0;
}

void draw_vao(struct Mesh mesh) {
    glBindVertexArray(mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertex_count);
}