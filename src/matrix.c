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

vec4 mat4MultiplyVec4(mat4 m, vec4 v) {
    vec4 result = {
        m.m[0][0]*v.x + m.m[0][1]*v.y + m.m[0][2]*v.z + m.m[0][3]*v.w,
        m.m[1][0]*v.x + m.m[1][1]*v.y + m.m[1][2]*v.z + m.m[1][3]*v.w,
        m.m[2][0]*v.x + m.m[2][1]*v.y + m.m[2][2]*v.z + m.m[2][3]*v.w,
        m.m[3][0]*v.x + m.m[3][1]*v.y + m.m[3][2]*v.z + m.m[3][3]*v.w,
    };
    return result;
}
