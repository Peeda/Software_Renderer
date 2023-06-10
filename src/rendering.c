#include "rendering.h"

u32* colorBuffer = NULL;
Texture bufferTexture;
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;


void setupRendering() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "test");
    SetTargetFPS(60);
    ToggleFullscreen();
    WINDOW_WIDTH = GetMonitorWidth(GetCurrentMonitor());
    WINDOW_HEIGHT = GetMonitorHeight(GetCurrentMonitor());

    colorBuffer = (u32*)malloc(sizeof(u32) * WINDOW_WIDTH * WINDOW_HEIGHT);

    Image tempImage = GenImageColor(WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);
    ImageFormat(&tempImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    bufferTexture = LoadTextureFromImage(tempImage);
}

void destroyRendering() {
    free(colorBuffer);
    UnloadTexture(bufferTexture);
    CloseWindow();
}

void resetBuffer(u32 color) {
    for (int i = 0; i < WINDOW_WIDTH; i++) {
        for (int k = 0; k < WINDOW_HEIGHT; k++) {
            drawPixel(i,k,color);
        }
    }
}

void CPURender() {
    //write from buffer to window
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            unsigned char r,g,b,a;
            u32 colorData = colorBuffer[y*WINDOW_WIDTH + x];
            int mask = 0xFF;
            r = (colorData >> 24) & mask;
            g = (colorData >> 16) & mask;
            b = (colorData >> 8) & mask;
            a = colorData & mask;
            DrawPixel(x,y,(Color){r,g,b,a});
        }
    }
    DrawFPS(10,10);
    EndDrawing();
}

void textureRender() {
    /*
     Quicker rendering of the pixel buffer to the screen using raylib's
     texture features, for some reason the format seems to be reading 
     ABGR from the hex values
    */

    resetBuffer(0xFFFF0000);
    UpdateTexture(bufferTexture, colorBuffer);
    //draw texture to screen
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(bufferTexture, 0, 0, WHITE);
        DrawFPS(10,10);
    EndDrawing();
}

void drawPixel(int x, int y, u32 color) {
    if (x < WINDOW_WIDTH && y < WINDOW_HEIGHT && x >= 0 && y >= 0) {
        colorBuffer[y*WINDOW_WIDTH + x] = color;
    } else {
        printf("drawPixel out of bounds, x is %d and y is %d\n", x, y);
    }
}

void drawGrid() {
    u32 white = 0x333333FF;
    for (int y = 0; y < WINDOW_HEIGHT; y += 10) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            drawPixel(x,y,white);
        }
    }
    for (int x = 0; x < WINDOW_WIDTH; x += 10) {
        for (int y = 0; y < WINDOW_HEIGHT; y++) {
            drawPixel(x,y,white);
        }
    }
}

void drawRectangle(int xStart, int yStart, int width, int height, u32 color) {
    //draw horizontal lines to create rect
    for (int y = yStart; y <= yStart+height; y++) {
        for (int x = xStart; x <= xStart+width; x++) {
            drawPixel(x,y,color);
        }
    }
}
