#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "raylib.h"

typedef uint32_t u32;

//RGBA
u32 *colorBuffer = NULL;
RenderTexture bufferTexture;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


int getBufferIndex(int y, int x);
void process_input();
void update();
void CPURender();
void render();

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "test");
    SetTargetFPS(60);
    colorBuffer = (u32*)malloc(sizeof(u32) * WINDOW_WIDTH * WINDOW_HEIGHT);
    bufferTexture = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

    for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++) {
        colorBuffer[i] = 0x000000FF;
    }

    while (!WindowShouldClose()) {
        process_input();
        update();
        CPURender();
        // render();
    }

    free(colorBuffer);
    UnloadRenderTexture(bufferTexture);
    CloseWindow();

    return 0;
}
int getBufferIndex(int y, int x) {
    return (y * WINDOW_WIDTH + x);
}
void process_input() {

}
void update() {

}
void CPURender() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            unsigned char r,g,b,a;
            u32 colorData = colorBuffer[y * WINDOW_WIDTH + x];
            int mask = 0xFF;
            r = (colorData >> 24) & mask;
            g = (colorData >> 16) & mask;
            b = (colorData >> 8) & mask;
            a = colorData & mask;
            if (r != 0) {
                printf("%d, %d, %d, %d\n", r, g, b, a);
            }
            DrawPixel(x,y,(Color){r,g,b,a});
        }
    }
    EndDrawing();
}
void render() {
    //draw buffer to texture
    UpdateTexture(bufferTexture.texture, colorBuffer);
    //draw texture to screen
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(bufferTexture.texture, 0, 0, WHITE);
    EndDrawing();
}
