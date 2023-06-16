#include "mesh.h"

vec3 cubeVertices[cubeVerticesNum] = {
    {5,5,5},
    {-1, -1, -1},
    {-1,  1, -1},
    { 1,  1, -1},
    { 1, -1, -1},
    {-1, -1,  1},
    {-1,  1,  1},
    { 1,  1,  1},
    { 1, -1,  1},
};

face faces[cubeFaceNum] = {
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
