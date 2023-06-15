#include "rendering.h"

Color* colorBuffer = NULL;
Texture bufferTexture;
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;


void setupRendering() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "test");
    SetTargetFPS(60);
    ToggleFullscreen();
    WINDOW_WIDTH = GetMonitorWidth(GetCurrentMonitor());
    WINDOW_HEIGHT = GetMonitorHeight(GetCurrentMonitor());

    colorBuffer = (Color*)malloc(sizeof(Color) * WINDOW_WIDTH * WINDOW_HEIGHT);

    Image tempImage = GenImageColor(WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);
    ImageFormat(&tempImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    bufferTexture = LoadTextureFromImage(tempImage);
}

void destroyRendering() {
    free(colorBuffer);
    UnloadTexture(bufferTexture);
    CloseWindow();
}

void resetBuffer(Color color) {
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
            /*
            unsigned char r,g,b,a;
            u32 colorData = colorBuffer[y*WINDOW_WIDTH + x];
            int mask = 0xFF;
            r = (colorData >> 24) & mask;
            g = (colorData >> 16) & mask;
            b = (colorData >> 8) & mask;
            a = colorData & mask;
            DrawPixel(x,y,(Color){r,g,b,a});
            */
            DrawPixel(x,y,colorBuffer[y*WINDOW_WIDTH + x]);
        }
    }
    DrawFPS(10,10);
    EndDrawing();
}


void textureRender() {
    UpdateTexture(bufferTexture, colorBuffer);
    //draw texture to screen
    BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(bufferTexture, 0, 0, WHITE);
        DrawFPS(10,10);
    EndDrawing();
}

void drawPixel(int x, int y, Color color) {
    if (x < WINDOW_WIDTH && y < WINDOW_HEIGHT && x >= 0 && y >= 0) {
        colorBuffer[y*WINDOW_WIDTH + x] = color;
    } else {
        printf("drawPixel out of bounds, x is %d and y is %d\n", x, y);
    }
}

void drawLine(int x1, int y1, int x2, int y2, Color color) {
    int deltaX = x2-x1;
    int deltaY = y2-y1;
    int length = abs(deltaX) > abs(deltaY) ? deltaX : deltaY;
    length = abs(length);
    float xInc = deltaX / (float)length;
    float yInc = deltaY / (float)length;
    float x = x1;
    float y = y1;
    for (int i = 0; i <= length; i++) {
        drawPixel(round(x),round(y),color);
        x += xInc;
        y += yInc;
    }
}

void lineTest() {
    drawLine(200,200,400,0,BLUE);
    drawLine(200,200,300,0,BLUE);
    drawLine(200,200,400,100,BLUE);

    drawLine(200,200,0,0,BLUE);
    drawLine(200,200,100,0,BLUE);
    drawLine(200,200,0,100,BLUE);

    drawLine(200,200,400,400,GREEN);
    drawLine(200,200,400,300,GREEN);
    drawLine(200,200,300,400,GREEN);

    drawLine(200,200,0,400,GREEN);
    drawLine(200,200,0,300,GREEN);
    drawLine(200,200,100,400,GREEN);

    drawLine(200,200,200,400, RED);
    drawLine(200,200,200,0, RED);
    drawLine(200,200,0,200, RED);
    drawLine(200,200,400,200, RED);
}

void drawGrid() {
    Color white = (Color){51,51,51,255};
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

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color) {
    drawLine(x1,y1,x2,y2,color);
    drawLine(x2,y2,x3,y3,color);
    drawLine(x3,y3,x1,y1,color);
}

void drawRectangle(int xStart, int yStart, int width, int height, Color color) {
    //draw horizontal lines to create rect
    for (int y = yStart; y <= yStart+height; y++) {
        for (int x = xStart; x <= xStart+width; x++) {
            drawPixel(x,y,color);
        }
    }
}
