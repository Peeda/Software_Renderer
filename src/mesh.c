#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "mesh.h"
#include "array.h"

mesh renderedMesh = {NULL, NULL, {0,0,0}};

vec3 cubeVertices[cubeVerticesNum] = {
    {-1, -1, -1},
    {-1,  1, -1},
    { 1,  1, -1},
    { 1, -1, -1},
    {-1, -1,  1},
    {-1,  1,  1},
    { 1,  1,  1},
    { 1, -1,  1},
};

face cubeFaces[cubeFaceNum] = {
    //front right back left top bottom
    {1,2,4},
    {2,3,4},

    {4,3,8},
    {3,7,8},

    {8,7,5},
    {7,6,5},

    {5,6,1},
    {6,2,1},

    {2,6,3},
    {6,7,3},

    {5,1,8},
    {1,4,8},
};

void loadCubeToMesh() {
    for (int i = 0; i < cubeVerticesNum; i++) {
        array_push(renderedMesh.vertices, cubeVertices[i]);
    }
    for (int i = 0; i < cubeFaceNum; i++) {
        array_push(renderedMesh.faces, cubeFaces[i]);
    }
}
void loadFileToMesh(char *path) {
    FILE *ptr;
    ptr = fopen(path, "r");

    if (ptr != NULL) {
        int size = 128;
        char buffer[size];
        for (int i = 0; i < size; i++) buffer[i] = '.';
        while (fgets(buffer,size,ptr) != NULL) {
            if (buffer[1] == ' ' && (buffer[0] == 'v' || buffer[0] == 'f')) {
                char line[64];
                //copy line data from buffer
                for (int i = 0; i < size; i++) {
                    line[i] = buffer[i];
                    if (buffer[i] == '\0') {
                        break;
                    }
                }
                //read 3 tokens from line
                if (buffer[0] == 'v') {
                    char *token = strtok(line, " ");
                    vec3 vertex;
                    int tokens = 3;
                    float data[tokens];
                    for (int i = 0; i < tokens; i++) {
                        token = strtok(NULL, " ");
                        data[i] = strtof(token, NULL);
                    }
                    vertex = (vec3){data[0],data[1],data[2]};
                    // printf("%f,%f,%f\n", vertex.x, vertex.y, vertex.z);
                    array_push(renderedMesh.vertices, vertex);
                } else if (buffer[0] == 'f') {
                    char *token = strtok(line, " ");
                    int tokens = 3;
                    int vertexIndices[3];
                    for (int i = 0; i < tokens; i++) {
                        token = strtok(NULL, " ");
                        int val = 0;
                        for (int k = 0; k < strlen(token); k++) {
                            if (token[k] == '/') break;
                            val *= 10;
                            val += (token[k] - '0');
                        }
                        vertexIndices[i] = val;
                    }
                    face currentFace = (face){vertexIndices[0],vertexIndices[1],vertexIndices[2]};
                    // printf("%d,%d,%d\n", currentFace.a, currentFace.b, currentFace.c);
                    array_push(renderedMesh.faces, currentFace);
                }
            }
        }
    }

    fclose(ptr);
}
