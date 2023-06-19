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

void vec2Print(vec2 a);
void vec3Print(vec3 a);

float vec2Magnitude(vec2 a);
vec2 vec2Add(vec2 a, vec2 b);
vec2 vec2Subtract(vec2 a, vec2 b);
void vec2Scale(vec2 *a, float factor);
void vec2Divide(vec2 *a, float factor);
void vec2Normalize(vec2 *a);

float vec3Magnitude(vec3 a);
vec3 vec3Add(vec3 a, vec3 b);
vec3 vec3Subtract(vec3 a, vec3 b);
void vec3Scale(vec3 *a, float factor);
void vec3Divide(vec3 *a, float factor);
void vec3Normalize(vec3 *a);

vec3 cross(vec3 a, vec3 b);
float dot(vec3 a, vec3 b);

vec3 rotateX(vec3 point, float angle);
vec3 rotateY(vec3 point, float angle);
vec3 rotateZ(vec3 point, float angle);

#endif
