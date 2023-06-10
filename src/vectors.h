#ifndef VECTOR_H
#define VECTOR_H


typedef struct {
    float x;
    float y;
} vec2;

typedef struct {
    float x;
    float y;
    float z;
} vec3;

vec3 rotateX(vec3 point, float angle);
vec3 rotateY(vec3 point, float angle);
vec3 rotateZ(vec3 point, float angle);

#endif
