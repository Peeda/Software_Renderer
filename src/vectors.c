#include <math.h>
#include <stdio.h>
#include "vectors.h"


float vec2Magnitude(vec2 a) {
    return sqrt(a.x*a.x + a.y*a.y);
}
vec2 vec2Add(vec2 a, vec2 b) {
    return (vec2){a.x + b.x, a.y + b.y};
}
vec2 vec2Subtract(vec2 a, vec2 b) {
    return (vec2){a.x - b.x, a.y - b.y};
}
vec2 vec2Scale(vec2 a, float factor) {
    return (vec2){a.x*factor, a.y*factor};
}
vec2 vec2Divide(vec2 a, float factor) {
    return (vec2){a.x/factor, a.y/factor};
}

float vec3Magnitude(vec3 a) {
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}
vec3 vec3Add(vec3 a, vec3 b) {
    return (vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}
vec3 vec3Subtract(vec3 a, vec3 b) {
    return (vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}
vec3 vec3Scale(vec3 a, float factor) {
    return (vec3){a.x*factor, a.y*factor, a.z*factor};
}
vec3 vec3Divide(vec3 a, float factor) {
    return (vec3){a.x/factor, a.y/factor, a.z/factor};
}

vec3 cross(vec3 a, vec3 b) {
    return (vec3){
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
}
vec3 dot(vec3 a, vec3 b) {
    return (vec3){a.x*b.x, a.y*b.y, a.z*b.z};
}

void vec2Print(vec2 a) {
    printf("{%f, %f}\n", a.x, a.y);
}
void vec3Print(vec3 a) {
    printf("{%f, %f, %f}\n", a.x, a.y, a.z);
}

vec3 rotateX(vec3 point, float angle) {
    return (vec3){
        point.x,
        point.y * cos(angle) - point.z * sin(angle),
        point.z * cos(angle) + point.y * sin(angle)
    };
}
vec3 rotateY(vec3 point, float angle) {
    return (vec3) {
        point.x * cos(angle) - point.z * sin(angle),
        point.y,
        point.z * cos(angle) + point.x * sin(angle)
    };
}
vec3 rotateZ(vec3 point, float angle) {
    return (vec3) {
        point.x * cos(angle) - point.y * sin(angle),
        point.y * cos(angle) + point.x * sin(angle),
        point.z
    };
}
