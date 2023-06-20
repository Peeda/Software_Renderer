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
    {1,2,4,RED},
    {2,3,4,RED},

    {4,3,8,BLUE},
    {3,7,8,BLUE},

    {8,7,5,GREEN},
    {7,6,5,GREEN},

    {5,6,1,YELLOW},
    {6,2,1,YELLOW},

    {2,6,3,PURPLE},
    {6,7,3,PURPLE},

    {5,1,8,BROWN},
    {1,4,8,BROWN},
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

    if (ptr == NULL) {
        fprintf(stderr, "Couldn't read file\n");
        fclose(ptr);
        return;
    }
    int size = 128;
    char buffer[size];
    while (fgets(buffer,size,ptr) != NULL) {
        if (buffer[1] == ' ' && (buffer[0] == 'v' || buffer[0] == 'f')) {
            //read 3 tokens from line
            char *token = strtok(buffer, " ");
            int tokens = 3;
            float vertexCoordinates[tokens];
            int vertexIndices[3];
            for (int i = 0; i < tokens; i++) {
                int val = 0;
                token = strtok(NULL, " ");
                if (buffer[0] == 'v') {
                    vertexCoordinates[i] = strtof(token, NULL);
                } else if (buffer[0] == 'f') {
                    for (int k = 0; k < strlen(token); k++) {
                        if (token[k] == '/') break;
                        val *= 10;
                        val += (token[k] - '0');
                    }
                    vertexIndices[i] = val;
                }
            }
            if (buffer[0] == 'v') {
                vec3 vertex = (vec3) {
                    vertexCoordinates[0],
                    vertexCoordinates[1],
                    vertexCoordinates[2],
                };
                array_push(renderedMesh.vertices, vertex);
            } else if (buffer[0] == 'f') {
                face currentFace = (face) {
                    vertexIndices[0],
                    vertexIndices[1],
                    vertexIndices[2],
                };
                array_push(renderedMesh.faces, currentFace);
            }
        }
    }

    fclose(ptr);
}
