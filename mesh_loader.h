#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#ifdef __cplusplus
extern "C" {
#endif

struct Mesh {
    GLuint vao;
    GLuint vertex_count;
};

int create_drawable(struct Mesh *out_mesh, int vertex_count, GLfloat *floats);
void draw_vao(struct Mesh mesh);

#ifdef __cplusplus
}
#endif

#endif /* MESH_LOADER_H */

