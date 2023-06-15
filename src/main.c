#include "rendering.h"
#include "mesh.h"


/////////////////////////////////
//          RENDERING          //
/////////////////////////////////
#define cubeSize 9*9*9
const float FOVFactor = 640;

vec3 cameraPos = {0,0,-5};
vec3 cubeRotation = {0,0,0};

void setup();
void render();
void process_input();
void update();

vec2 projectedTriangles[faceNum][3];

int main() {

    setupRendering();
    setup();
    while (!WindowShouldClose()) {
        process_input();
        update();
        render();
    }
    destroyRendering();
    return 0;
}
void setup() {
}

vec2 project(vec3 point) {
    vec2 out = {FOVFactor * point.x / point.z, FOVFactor * point.y / point.z};
    return out;
}

void process_input() {

}

void update() {
    cubeRotation.x += 0.01;
    // cubeRotation.y += 0.01;
    // cubeRotation.z += 0.01;
    for (int faceInd = 0; faceInd < faceNum; faceInd++) {
        //convert a face to a 2d triangle
        vec3 facePoints[3];
        //get the 3d points for the current triangle
        face currFace = faces[faceInd];
        facePoints[0] = vertices[currFace.a];
        facePoints[1] = vertices[currFace.b];
        facePoints[2] = vertices[currFace.c];
        //transform
        for (int i = 0; i < 3; i++) {
            //rotate
            facePoints[i] = rotateX(facePoints[i], cubeRotation.x);
            facePoints[i] = rotateY(facePoints[i], cubeRotation.y);
            facePoints[i] = rotateZ(facePoints[i], cubeRotation.z);
            //translate w/ camera
            facePoints[i].z -= cameraPos.z;
            //project
            projectedTriangles[faceInd][i] = project(facePoints[i]);
        }
    }
}
void render() {
    resetBuffer(BLACK);
    drawGrid();
    for (int faceInd = 0; faceInd < faceNum; faceInd++) {
        vec2 pointArr[3];
        for (int i = 0; i < 3; i++) {
            vec2 point = projectedTriangles[faceInd][i];
            pointArr[i] = (vec2){point.x + (float)WINDOW_WIDTH/2, point.y + (float)WINDOW_HEIGHT/2};
        }
        drawTriangle(pointArr[0].x, pointArr[0].y, pointArr[1].x, pointArr[1].y, pointArr[2].x, pointArr[2].y, PURPLE);
    }
    textureRender();
}
