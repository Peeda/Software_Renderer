#ifndef MATRIX
#define MATRIX

#include "vectors.h"

typedef struct {
    float m[4][4];
} mat4;

mat4 mat4Identity();
mat4 mat4Scaling(float x, float y, float z);
vec4 mat4MultiplyVec4(mat4 m, vec4 v);


#endif
