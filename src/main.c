#include "rendering.h"
#include "mesh.h"
#include "array.h"


/////////////////////////////////
//          RENDERING          //
/////////////////////////////////
const float FOVFactor = 640;

vec3 cameraPos = {0,0,-5};

void setup();
void render();
void process_input();
void update();
void freeResources();

triangle *projectedTriangles = NULL;

int main() {
    setupRendering();
    setup();
    while (!WindowShouldClose()) {
        process_input();
        update();
        render();
    }

    destroyRendering();
    freeResources();
    return 0;
}
void setup() {
    // loadFileToMesh("./assets/f22.obj");
    loadFileToMesh("./assets/drone.obj");
}

vec2 project(vec3 point) {
    vec2 out = {FOVFactor * point.x / point.z, FOVFactor * point.y / point.z};
    return out;
}

void process_input() {

}

void update() {
    array_free(projectedTriangles);
    projectedTriangles = NULL;

    renderedMesh.rotation.x += 0.01;
    renderedMesh.rotation.y += 0.01;
    for (int faceInd = 0; faceInd < array_length(renderedMesh.faces); faceInd++) {
        //convert a face to a 2d triangle
        vec3 facePoints[3];
        //get the 3d points for the current triangle
        face currFace = renderedMesh.faces[faceInd];
        facePoints[0] = renderedMesh.vertices[currFace.a-1];
        facePoints[1] = renderedMesh.vertices[currFace.b-1];
        facePoints[2] = renderedMesh.vertices[currFace.c-1];
        //transform and save to triangle
        triangle toPush;
        for (int i = 0; i < 3; i++) {
            //rotate
            facePoints[i] = rotateX(facePoints[i], renderedMesh.rotation.x);
            facePoints[i] = rotateY(facePoints[i], renderedMesh.rotation.y);
            facePoints[i] = rotateZ(facePoints[i], renderedMesh.rotation.z);
            //translate w/ camera
            facePoints[i].z -= cameraPos.z;
            //project and add to triangle
            toPush.points[i] = project(facePoints[i]);
        }
        array_push(projectedTriangles,toPush);
    }
}
void render() {
    resetBuffer(BLACK);
    drawGrid();
    // lineTest();
    for (int faceInd = 0; faceInd < array_length(projectedTriangles); faceInd++) {
        vec2 pointArr[3];
        for (int i = 0; i < 3; i++) {
            vec2 point = projectedTriangles[faceInd].points[i];
            pointArr[i] = (vec2){point.x + (float)WINDOW_WIDTH/2, point.y + (float)WINDOW_HEIGHT/2};
        }
        drawTriangle(pointArr[0].x, pointArr[0].y, pointArr[1].x, pointArr[1].y, pointArr[2].x, pointArr[2].y, PURPLE);
    }
    textureRender();
}
void freeResources() {
    free(colorBuffer);
    array_free(renderedMesh.vertices);
    array_free(renderedMesh.faces);
    array_free(projectedTriangles);
}
