#include "rendering.h"
#include "mesh.h"
#include "array.h"
#include "matrix.h"

const float FOVFactor = 640;
vec3 cameraPos = {0,0,0};

bool useCulling;
bool painters;
enum renderMethod {
    WIREFRAME,
    WIREFRAME_DOTS,
    FILL,
    FILL_WIREFRAME
} renderMethod;

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
    useCulling = true;
    painters = false;
    renderMethod = WIREFRAME;
    // loadFileToMesh("./assets/cube.obj");
    // loadFileToMesh("./assets/drone.obj");
    loadCubeToMesh();
}

vec2 project(vec3 point) {
    vec2 out = {FOVFactor * point.x / point.z, FOVFactor * point.y / point.z};
    return out;
}

void process_input() {
    if (IsKeyPressed(KEY_C)) {
        useCulling = !useCulling;
    }
    if (IsKeyPressed(KEY_P)) {
        painters = !painters;
    }
    if (IsKeyPressed(KEY_ONE)) {
        renderMethod = WIREFRAME;
    }
    if (IsKeyPressed(KEY_TWO)) {
        renderMethod = WIREFRAME_DOTS;
    }
    if (IsKeyPressed(KEY_THREE)) {
        renderMethod = FILL;
    }
    if (IsKeyPressed(KEY_FOUR)) {
        renderMethod = FILL_WIREFRAME;
    }
}
void update() {
    array_free(projectedTriangles);
    projectedTriangles = NULL;

    renderedMesh.rotation.x += 0.01;
    renderedMesh.rotation.y += 0.01;
    renderedMesh.rotation.z += 0.01;

    renderedMesh.scale.x += 0.001;
    renderedMesh.scale.y += 0.001;
    renderedMesh.scale.z += 0.001;

    // renderedMesh.translation.x += 0.01;
    renderedMesh.translation.z = 5;
    mat4 scaleMatrix = mat4Scaling(
        renderedMesh.scale.x,
        renderedMesh.scale.y,
        renderedMesh.scale.z
    );
    mat4 translationMatrix = mat4Translation(
        renderedMesh.translation.x,
        renderedMesh.translation.y,
        renderedMesh.translation.z
    );
    mat4 rotationMatrices[3];
    rotationMatrices[0] = mat4XRotation(renderedMesh.rotation.x);
    rotationMatrices[1] = mat4YRotation(renderedMesh.rotation.y);
    rotationMatrices[2] = mat4ZRotation(renderedMesh.rotation.z);

    mat4 worldMatrix = mat4Identity();
    worldMatrix = mat4MultiplyMat4(scaleMatrix,worldMatrix);
    for (int i = 0; i < 3; i++) {
        worldMatrix = mat4MultiplyMat4(rotationMatrices[i],worldMatrix);
    }
    worldMatrix = mat4MultiplyMat4(translationMatrix,worldMatrix);

    //loop through each face and project it to a triangle
    for (int faceInd = 0; faceInd < array_length(renderedMesh.faces); faceInd++) {
        vec4 facePoints[3];
        //get the 3d points for the current face
        face currFace = renderedMesh.faces[faceInd];
        facePoints[0] = makeVec4(renderedMesh.vertices[currFace.a-1]);
        facePoints[1] = makeVec4(renderedMesh.vertices[currFace.b-1]);
        facePoints[2] = makeVec4(renderedMesh.vertices[currFace.c-1]);
        //transform the points
        for (int i = 0; i < 3; i++) {
            facePoints[i] = mat4MultiplyVec4(worldMatrix, facePoints[i]);
        }
        if (useCulling) {
            // 0 -> A
            // 1 -> B
            // 2 -> C
            vec3 A = makeVec3(facePoints[0]);
            vec3 B = makeVec3(facePoints[1]);
            vec3 C = makeVec3(facePoints[2]);
            vec3 AB = vec3Subtract(B,A);
            vec3 AC = vec3Subtract(C,A);
            vec3 faceNormal = cross(AB, AC);
            vec3Normalize(&faceNormal);
            //ray from a point on the face to the camera
            vec3 cameraRay = vec3Subtract(cameraPos, B);
            float dotProduct = dot(faceNormal, cameraRay);
            if (dotProduct < 0) {
                //don't render if the face points away from the camera
                continue;
            }
        }
        triangle toPush;
        toPush.color = currFace.color;
        float avgDepth = 0;
        for (int i = 0; i < 3; i++) {
            avgDepth += facePoints[i].z;
        }
        avgDepth /= 3;
        toPush.depth = avgDepth;
        for (int i = 0; i < 3; i++) {
            //project and scale to screen
            toPush.points[i] = project(makeVec3(facePoints[i]));
            toPush.points[i].x += (float)WINDOW_WIDTH/2;
            toPush.points[i].y += (float)WINDOW_HEIGHT/2;
        }
        array_push(projectedTriangles,toPush);
    }
    if (painters) {
        for (int i = 1; i < array_length(projectedTriangles); i++) {
            int k = i;
            while (k>0 && projectedTriangles[k].depth > projectedTriangles[k-1].depth) {
                triangle tmp = projectedTriangles[k-1];
                projectedTriangles[k-1] = projectedTriangles[k];
                projectedTriangles[k] = tmp;
                k--;
            }
        }
    }
}
void render() {
    resetBuffer(BLACK);
    drawGrid();
    for (int faceInd = 0; faceInd < array_length(projectedTriangles); faceInd++) {
        triangle tri = projectedTriangles[faceInd];
        if (renderMethod == WIREFRAME) {
            drawTriangle(tri.points[0].x, tri.points[0].y, 
                         tri.points[1].x, tri.points[1].y, 
                         tri.points[2].x, tri.points[2].y, RED);
        } else if (renderMethod == WIREFRAME_DOTS){
            drawTriangle(tri.points[0].x, tri.points[0].y, 
                         tri.points[1].x, tri.points[1].y, 
                         tri.points[2].x, tri.points[2].y, RED);
            for (int i = 0; i < 3; i++) {
                drawRectangle(tri.points[i].x-5,tri.points[i].y-5,10,10,WHITE);
            }
        } else if (renderMethod == FILL) {
            fillTriangle(tri.points[0].x, tri.points[0].y, 
                         tri.points[1].x, tri.points[1].y, 
                         tri.points[2].x, tri.points[2].y, tri.color);
        } else if (renderMethod == FILL_WIREFRAME) {
            fillTriangle(tri.points[0].x, tri.points[0].y, 
                         tri.points[1].x, tri.points[1].y, 
                         tri.points[2].x, tri.points[2].y, tri.color);
            drawTriangle(tri.points[0].x, tri.points[0].y, 
                         tri.points[1].x, tri.points[1].y, 
                         tri.points[2].x, tri.points[2].y, BLACK);
        }
    }
    textureRender();
}
void freeResources() {
    free(colorBuffer);
    array_free(renderedMesh.vertices);
    array_free(renderedMesh.faces);
    array_free(projectedTriangles);
}
