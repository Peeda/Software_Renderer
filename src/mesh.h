#ifndef MESH
#define MESH

#include "vectors.h"
#include "triangle.h"

//leave an empty index
#define meshVertices 8 + 1
extern vec3 vertices[meshVertices];

#define faceNum 12
extern face faces[faceNum];

#endif
