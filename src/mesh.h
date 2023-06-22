#ifndef MESH
#define MESH

#include "vectors.h"
#include "triangle.h"

#define cubeVerticesNum 8
extern vec3 cubeVertices[cubeVerticesNum];
#define cubeFaceNum 12
extern face cubeFaces[cubeFaceNum];

typedef struct {
    vec3 *vertices;
    face *faces;
    vec3 rotation;
    vec3 scale;
    vec3 translation;
} mesh;

extern mesh renderedMesh;
void loadCubeToMesh();
void loadFileToMesh(char *path);

#endif
