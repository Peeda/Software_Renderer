#ifndef LIGHT
#define LIGHT

#include <raylib.h>
#include "vectors.h"

typedef struct {
    vec3 dir;
} light;

Color applyLightIntensity(Color c, float intensity);

#endif
