#ifndef TRIANGLE
#define TRIANGLE

#include "vectors.h"

//stores 3 indices that refer to vec3
typedef struct {
    int a;
    int b;
    int c;
} face;

typedef struct {
    vec2 points[3];
} triangle;

#endif
