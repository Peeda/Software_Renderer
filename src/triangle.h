#ifndef TRIANGLE
#define TRIANGLE

#include <raylib.h>
#include "vectors.h"

//stores 3 indices that refer to vec3
typedef struct {
    int a;
    int b;
    int c;
    Color color;
    vec2 aTexture;
    vec2 bTexture;
    vec2 cTexture;
} face;

typedef struct {
    vec2 points[3];
    vec2 texturePoints[3];
    Color color;
    float depth;
} triangle;

#endif
