#include "light.h"

Color applyLightIntensity(Color c, float intensity) {
    if (intensity < 0) {
        intensity = 0;
    }
    if (intensity > 1) {
        intensity = 1;
    }
    return (Color) {
        c.r*intensity,
        c.g*intensity,
        c.b*intensity,
        c.a
    };
}
