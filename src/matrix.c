#include "matrix.h"

mat4 mat4Identity() {
    mat4 identity = {{
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    }};
    return identity;
}
mat4 mat4Scaling(float x, float y, float z) {
    mat4 scalingMat = mat4Identity();
    scalingMat.m[0][0] = x;
    scalingMat.m[1][1] = y;
    scalingMat.m[2][2] = z;
    return scalingMat;
}
mat4 mat4Translation(float tx, float ty, float tz) {
    mat4 translationMat = mat4Identity();
    translationMat.m[0][3] = tx;
    translationMat.m[1][3] = ty;
    translationMat.m[2][3] = tz;
    return translationMat;
}
mat4 mat4XRotation(float angle) {
    mat4 rotationMat = mat4Identity();
    rotationMat.m[1][1] = cos(angle);
    rotationMat.m[1][2] = sin(angle) * -1;

    rotationMat.m[2][1] = sin(angle);
    rotationMat.m[2][2] = cos(angle);
    return rotationMat;
}
mat4 mat4YRotation(float angle) {
    mat4 rotationMat = mat4Identity();
    rotationMat.m[0][0] = cos(angle);
    rotationMat.m[0][2] = sin(angle) * -1;

    rotationMat.m[2][0] = sin(angle);
    rotationMat.m[2][2] = cos(angle);
    return rotationMat;
}
mat4 mat4ZRotation(float angle) {
    mat4 rotationMat = mat4Identity();
    rotationMat.m[0][0] = cos(angle);
    rotationMat.m[0][1] = sin(angle);

    rotationMat.m[1][0] = sin(angle) * -1;
    rotationMat.m[1][1] = cos(angle);
    return rotationMat;
}

vec4 mat4MultiplyVec4(mat4 m, vec4 v) {
    vec4 result = {
        m.m[0][0]*v.x + m.m[0][1]*v.y + m.m[0][2]*v.z + m.m[0][3]*v.w,
        m.m[1][0]*v.x + m.m[1][1]*v.y + m.m[1][2]*v.z + m.m[1][3]*v.w,
        m.m[2][0]*v.x + m.m[2][1]*v.y + m.m[2][2]*v.z + m.m[2][3]*v.w,
        m.m[3][0]*v.x + m.m[3][1]*v.y + m.m[3][2]*v.z + m.m[3][3]*v.w,
    };
    return result;
}
mat4 mat4MultiplyMat4(mat4 a, mat4 b) {
    mat4 outputMat;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            outputMat.m[row][col] = 0;
            for (int i = 0; i < 4; i++) {
                outputMat.m[row][col] += a.m[row][i] * b.m[i][col];
            }
        }
    }
    return outputMat;
}
mat4 mat4Projection(float fov, float aspect, float zNear, float zFar) {
    mat4 outputMat = {{{0}}};
    outputMat.m[0][0] = 1/(aspect * tan(fov/2));
    outputMat.m[1][1] = 1/tan(fov/2);
    outputMat.m[2][2] = zFar / (zFar-zNear);
    outputMat.m[2][3] = (-zFar * zNear) / (zFar - zNear);
    outputMat.m[3][2] = 1;
    return outputMat;
}
void mat4Print(mat4 a) {
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 4; k++) {
            printf("%f ", a.m[i][k]);
        }
        printf("\n");
    }
    printf("\n");
}
