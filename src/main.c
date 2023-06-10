#include "rendering.h"


/////////////////////////////////
//          RENDERING          //
/////////////////////////////////
#define cubeSize 9*9*9
vec3 cubePoints[cubeSize];
vec2 projectedPoints[cubeSize];
const float FOVFactor = 640;

vec3 cameraPos = {0,0,-5};
vec3 cubeRotation = {0,0,0};

void setup();
void render();
void process_input();
void update();

int main() {

    setupRendering();
    setup();
    while (!WindowShouldClose()) {
        /*
        // Color temp = RED;
        u32 temp = 0xFF0000FF;
        unsigned char * pointer = &temp;
        for (int i = 0; i < 4; i++) {
            printf("%d,", (int)(*pointer));
            pointer++;
        }
        printf("\n");
        */
        process_input();
        update();
        render();
    }
    destroyRendering();
    return 0;
}
void setup() {
    int ind = 0;
    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                //TODO: test this with different orders, using .z=z notation
                cubePoints[ind] = (vec3){x,y,z};
                ind++;
            }
        }
    }
}

vec2 project(vec3 point) {
    vec2 out = {FOVFactor * point.x / point.z, FOVFactor * point.y / point.z};
    return out;
}

void process_input() {

}

void update() {
    cubeRotation.y += 0.1;
    for (int i = 0; i < cubeSize; i++) {
        vec3 point = cubePoints[i];
        //transform point
        point = rotateY(point, cubeRotation.y);
        //account for camera distance
        point.z = point.z - cameraPos.z;
        projectedPoints[i] = project(point);
    }
}
void render() {
    drawGrid();
    for (int i = 0; i < cubeSize; i++) {
        vec2 point = projectedPoints[i];
        drawRectangle(point.x + (float)WINDOW_WIDTH/2, point.y + (float)WINDOW_HEIGHT/2, 3, 3, 0xFF0000FF);
    }
    
    // CPURender();
    textureRender();

    resetBuffer(0x000000FF);
}
