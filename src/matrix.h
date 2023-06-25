#ifndef MATRIX
#define MATRIX

#include <math.h>
#include <stdio.h>
#include "vectors.h"

typedef struct {
    float m[4][4];
} mat4;

mat4 mat4Identity();
mat4 mat4Scaling(float x, float y, float z);
mat4 mat4Translation(float tx, float ty, float tz);
mat4 mat4XRotation(float angle);
mat4 mat4YRotation(float angle);
mat4 mat4ZRotation(float angle);
mat4 mat4Projection(float fov, float aspect, float zNear, float zFar);
vec4 applyProjectionMatrix(mat4 projection, vec4 vec);
vec4 mat4MultiplyVec4(mat4 m, vec4 v);
mat4 mat4MultiplyMat4(mat4 a, mat4 b);
void mat4Print(mat4 a);


#endif
