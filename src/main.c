#include "rendering.h"
#include "mesh.h"
#include "array.h"
#include "matrix.h"
#include "light.h"
#include "texture.h"

mat4 projectionMatrix;
light worldLight;
vec3 cameraPos = {0,0,0};

bool useCulling;
bool painters;
bool frameByFrame;
enum renderMethod {
    WIREFRAME,
    WIREFRAME_DOTS,
    FILL,
    FILL_WIREFRAME,
    TEXTURED,
    TEXTURED_WIREFRAME
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
        if (frameByFrame) WaitTime(1);
    }

    destroyRendering();
    freeResources();
    return 0;
}
void setup() {
    useCulling = true;
    painters = false;
    frameByFrame = false;
    renderMethod = WIREFRAME;

    float aspectRatio = (float)WINDOW_WIDTH/WINDOW_HEIGHT;
    vec3 lightDir = {0,1,1};
    vec3Normalize(&lightDir);
    worldLight = (light){lightDir};
    projectionMatrix = mat4Projection(PI/3,aspectRatio,0.1,100);

    uint32_t *intermediate = (uint32_t*)REDBRICK_TEXTURE;
    for (int i = 0; i < 64*64; i++) {
        uint32_t curr = intermediate[i];
        int r,g,b,a;
        int mask = 0xFF;
        a = (curr >> 24) & mask;
        r = (curr >> 16) & mask;
        g = (curr >> 8) & mask;
        b = curr & mask;
        meshTexture[i] = (Color){r,g,b,a};
    }
    for (int y = 0; y < 64; y++) {
        for (int x = 0; x < 64; x++) {
            int val = y ^ x;
            // meshTexture[y*64 +x] = (Color){val,val,val,255};
        }
    }

    // loadFileToMesh("./assets/f22.obj");
    // loadFileToMesh("./assets/cube.obj");
    // loadFileToMesh("./assets/drone.obj");
    loadCubeToMesh();
}

void process_input() {
    if (IsKeyPressed(KEY_C)) {
        useCulling = !useCulling;
    }
    if (IsKeyPressed(KEY_P)) {
        painters = !painters;
    }
    if (IsKeyPressed(KEY_F)) {
        frameByFrame = !frameByFrame;
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
    if (IsKeyPressed(KEY_FIVE)) {
        renderMethod = TEXTURED;
    }
    if (IsKeyPressed(KEY_SIX)) {
        renderMethod = TEXTURED_WIREFRAME;
    }
}
void update() {
    array_free(projectedTriangles);
    projectedTriangles = NULL;

    renderedMesh.rotation.x += 0.01;
    renderedMesh.rotation.y += 0.01;
    renderedMesh.rotation.z += 0.01;

    // renderedMesh.scale.x += 0.001;
    // renderedMesh.scale.y += 0.001;
    // renderedMesh.scale.z += 0.001;

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
    worldMatrix = mat4MultiplyMat4(projectionMatrix, worldMatrix);

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
        if (dotProduct < 0 && useCulling) {
            //don't render if the face points away from the camera
            continue;
        }

        //calculate lighting with the inverse of the light ray
        float lightDotProduct = -dot(faceNormal, worldLight.dir);
        // -1 -> 0
        // 1 -> 1
        lightDotProduct++;
        lightDotProduct /= 2;
        Color shadedColor = applyLightIntensity(currFace.color, lightDotProduct);

        float avgDepth = 0;
        for (int i = 0; i < 3; i++) {
            avgDepth += facePoints[i].z;
        }
        vec4 projectedPoints[3];
        for (int i = 0; i < 3; i++) {
            //project and scale to screen
            projectedPoints[i] = perspectiveDivide(facePoints[i]);

            projectedPoints[i].y *= -1;

            projectedPoints[i].x *= (float)WINDOW_WIDTH/2;
            projectedPoints[i].y *= (float)WINDOW_HEIGHT/2;
            projectedPoints[i].x += (float)WINDOW_WIDTH/2;
            projectedPoints[i].y += (float)WINDOW_HEIGHT/2;
        }
        triangle toPush;
        vec2 uvCoordinates[3];
        uvCoordinates[0] = (vec2){currFace.aTexture.x,currFace.aTexture.y};
        uvCoordinates[1] = (vec2){currFace.bTexture.x,currFace.bTexture.y};
        uvCoordinates[2] = (vec2){currFace.cTexture.x,currFace.cTexture.y};
        for (int i = 0; i < 3; i++) {
            toPush.points[i].x = projectedPoints[i].x;
            toPush.points[i].y = projectedPoints[i].y;
            toPush.texturePoints[i] = uvCoordinates[i];
        }
        toPush.color = shadedColor;
        toPush.depth = avgDepth;
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
        if (renderMethod == WIREFRAME || renderMethod == WIREFRAME_DOTS) {
            drawTriangle(tri, RED);
            if (renderMethod == WIREFRAME_DOTS) {
                for (int i = 0; i < 3; i++) {
                    drawRectangle(tri.points[i].x-2,tri.points[i].y-2,4,4,WHITE);
                }
            }
        } else if (renderMethod == FILL || renderMethod == FILL_WIREFRAME) {
            fillTriangle(tri, tri.color);
            if (renderMethod == FILL_WIREFRAME) {
                drawTriangle(tri, BLACK);
            }
        } else if (renderMethod == TEXTURED || renderMethod == TEXTURED_WIREFRAME) {
            textureTriangle(tri, meshTexture);
            if (renderMethod == TEXTURED_WIREFRAME) {
                drawTriangle(tri, BLACK);
            }
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
