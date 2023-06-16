#include <stdio.h>
#include "mesh.h"
#include "array.h"

mesh renderedMesh = {NULL, NULL, {0,0,0}};

vec3 cubeVertices[cubeVerticesNum] = {
    {-1, -1, -1},
    {-1,  1, -1},
    { 1,  1, -1},
    { 1, -1, -1},
    {-1, -1,  1},
    {-1,  1,  1},
    { 1,  1,  1},
    { 1, -1,  1},
};

face cubeFaces[cubeFaceNum] = {
    //front right back left top bottom
    {1,2,4},
    {2,3,4},

    {4,3,8},
    {3,7,8},

    {8,7,5},
    {7,6,5},

    {5,6,1},
    {6,2,1},

    {2,6,3},
    {6,7,3},

    {5,1,8},
    {1,4,8},
};

void loadCubeToMesh() {
    for (int i = 0; i < cubeVerticesNum; i++) {
        array_push(renderedMesh.vertices, cubeVertices[i]);
    }
    for (int i = 0; i < cubeFaceNum; i++) {
        array_push(renderedMesh.faces, cubeFaces[i]);
    }
}
