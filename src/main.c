#include "rendering.h"
#include "mesh.h"
#include "array.h"


/////////////////////////////////
//          RENDERING          //
/////////////////////////////////
const float FOVFactor = 640;

vec3 cameraPos = {0,0,0};

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
    loadFileToMesh("./assets/drone.obj");
    // loadFileToMesh("./assets/cube.obj");
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
            //translate away from camera
            facePoints[i].z += 5;
        }
        //backface culling
        // 0 -> A
        // 1 -> B
        // 2 -> C
        vec3 AB = vec3Subtract(facePoints[1],facePoints[0]);
        vec3 AC = vec3Subtract(facePoints[2],facePoints[0]);
        vec3 faceNormal = cross(AB, AC);
        vec3Normalize(&faceNormal);
        //ray from a point on the face to the camera
        vec3 cameraRay = vec3Subtract(cameraPos, facePoints[1]);
        float dotProduct = dot(faceNormal, cameraRay);
        if (dotProduct < 0) {
            //don't render if the face points away from the camera
            continue;
        }

        for (int i = 0; i < 3; i++) {
            //project and scale to screen
            toPush.points[i] = project(facePoints[i]);
            toPush.points[i].x += (float)WINDOW_WIDTH/2;
            toPush.points[i].y += (float)WINDOW_HEIGHT/2;
        }
        array_push(projectedTriangles,toPush);
    }
}
void render() {
    resetBuffer(BLACK);
    drawGrid();
    for (int faceInd = 0; faceInd < array_length(projectedTriangles); faceInd++) {
        triangle tri = projectedTriangles[faceInd];
        fillTriangle(tri.points[0].x, tri.points[0].y, 
                     tri.points[1].x, tri.points[1].y, 
                     tri.points[2].x, tri.points[2].y, WHITE);
        drawTriangle(tri.points[0].x, tri.points[0].y, 
                     tri.points[1].x, tri.points[1].y, 
                     tri.points[2].x, tri.points[2].y, BLACK);
    }
    textureRender();
}
void freeResources() {
    free(colorBuffer);
    array_free(renderedMesh.vertices);
    array_free(renderedMesh.faces);
    array_free(projectedTriangles);
}
