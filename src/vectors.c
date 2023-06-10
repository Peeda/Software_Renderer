#include <math.h>
#include "vectors.h"

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
