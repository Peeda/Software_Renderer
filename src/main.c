#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "raylib.h"

typedef uint32_t u32;

//RGBA
u32 *colorBuffer = NULL;
Texture bufferTexture;
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;


int getIndex(int y, int x);
void process_input();
void update();
void CPURender();
void render();
void resetBuffer();
void drawGrid();
void drawRectangle(int xStart, int yStart, int width, int height, u32 color);

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "test");
    SetTargetFPS(60);
    ToggleFullscreen();
    WINDOW_WIDTH = GetMonitorWidth(GetCurrentMonitor());
    WINDOW_HEIGHT = GetMonitorHeight(GetCurrentMonitor());
    colorBuffer = (u32*)malloc(sizeof(u32) * WINDOW_WIDTH * WINDOW_HEIGHT);

    Image tempImage = GenImageColor(WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);
    ImageFormat(&tempImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    bufferTexture = LoadTextureFromImage(tempImage);

    while (!WindowShouldClose()) {
        process_input();
        update();
        render();
    }

    free(colorBuffer);
    UnloadTexture(bufferTexture);
    CloseWindow();

    return 0;
}
void process_input() {

}
void update() {

}
void render() {
    resetBuffer();
    drawRectangle(200,200,500,500,0xFFFF00FF);
    // drawGrid();
    //write from buffer to window
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            unsigned char r,g,b,a;
            u32 colorData = colorBuffer[getIndex(y,x)];
            int mask = 0xFF;
            r = (colorData >> 24) & mask;
            g = (colorData >> 16) & mask;
            b = (colorData >> 8) & mask;
            a = colorData & mask;
            DrawPixel(x,y,(Color){r,g,b,a});
        }
    }
    EndDrawing();
}
void Texturerender() {
    //draw buffer to texture
    UpdateTexture(bufferTexture, colorBuffer);
    //draw texture to screen
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(bufferTexture, 0, 0, WHITE);
    EndDrawing();
}
int getIndex(int y, int x) {
    int out = y*WINDOW_WIDTH + x;
    if (out > WINDOW_HEIGHT*WINDOW_WIDTH) {
        printf("Hey, this %d,%d is too big.\n",y,x);
    }
    return out;
}
void resetBuffer() {
    for (int i = 0; i < WINDOW_HEIGHT * WINDOW_WIDTH; i++) {
        colorBuffer[i] = 0x000000FF;
    }
}
void drawGrid() {
    u32 white = 0x333333FF;
    for (int y = 0; y < WINDOW_HEIGHT; y += 10) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            colorBuffer[getIndex(y,x)] = white;
        }
    }
    for (int x = 0; x < WINDOW_WIDTH; x += 10) {
        for (int y = 0; y < WINDOW_HEIGHT; y++) {
            colorBuffer[getIndex(y,x)] = white;
        }
    }
}
void drawRectangle(int xStart, int yStart, int width, int height, u32 color) {
    //draw horizontal lines to create rect
    for (int y = yStart; y <= yStart+height; y++) {
        for (int x = xStart; x <= xStart+width; x++) {
            colorBuffer[getIndex(y,x)] = color;
        }
    }
}
