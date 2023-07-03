#include <assert.h>
#include "rendering.h"
#include "texture.h"

Color* colorBuffer = NULL;
Texture bufferTexture;
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;


void setupRendering() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "test");
    SetTargetFPS(60);
    ToggleFullscreen();
    if (IsWindowFullscreen()) {
        WINDOW_WIDTH = GetMonitorWidth(GetCurrentMonitor());
        WINDOW_HEIGHT = GetMonitorHeight(GetCurrentMonitor());
    }

    colorBuffer = (Color*)malloc(sizeof(Color) * WINDOW_WIDTH * WINDOW_HEIGHT);

    Image tempImage = GenImageColor(WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);
    ImageFormat(&tempImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    bufferTexture = LoadTextureFromImage(tempImage);
}

void destroyRendering() {
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

void drawTriangle(triangle tri, Color color) {
    int x1 = tri.points[0].x;
    int y1 = tri.points[0].y;
    int x2 = tri.points[1].x;
    int y2 = tri.points[1].y;
    int x3 = tri.points[2].x;
    int y3 = tri.points[2].y;
    drawLine(x1,y1,x2,y2,color);
    drawLine(x2,y2,x3,y3,color);
    drawLine(x3,y3,x1,y1,color);
}
void intSwap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void floatSwap(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}
void fillFlatBottom(int x1, int y1, int mx, int my, int x2, int y2, Color color) {
    //points 1 and m are the bottom, 2 is the top
    //y2 should be higher up than the other two points
    assert(y2 <= y1 && y2 <= my);
    assert(y1-y2 != 0 && my-y2 != 0);
    //iterate from the top down, drawing scanlines
    if (mx < x1) {
        intSwap(&mx,&x1);
        intSwap(&my,&y1);
    }
    //rate of change for x with respect to y
    float slopeOne = (float)(x1-x2)/(y1-y2);
    float slopeTwo = (float)(mx-x2)/(my-y2);
    float leftX = x2;
    float rightX = x2;

    for (int y = y2+1; y <= y1; y++) {
        leftX += slopeOne;
        rightX += slopeTwo;
        int lBound = round(leftX);
        int rBound = round(rightX);
        for (int x = lBound; x <= rBound; x++) {
            drawPixel(x,y,color);
        }
    }
}
void fillFlatTop(int x1, int y1, int mx, int my, int x2, int y2, Color color) {
    //point 2 should be the bottom point
    //point 1 should be on the left and point m on the right
    assert(y2 >= y1 && y2 >= my);
    assert(y1-y2 != 0 && my-y2 != 0);
    if (x1 > mx) {
        intSwap(&x1,&mx);
        intSwap(&y1,&my);
    }
    //change in x as y decreases
    float leftX = x2;
    float rightX = x2;
    float slopeOne = (float)(x1-x2)/(y1-y2);
    float slopeTwo = (float)(mx-x2)/(my-y2);

    for (int y = y2-1; y >= y1; y--) {
        leftX -= slopeOne;
        rightX -= slopeTwo;
        int lBound = round(leftX);
        int rBound = round(rightX);
        for (int x = lBound; x <= rBound; x++) {
            drawPixel(x,y,color);
        }
    }
}
void fillTriangle(triangle tri, Color color) {
    //find mx and my
    //bubble sort the coordinates in ascending y order

    int x1 = tri.points[0].x;
    int y1 = tri.points[0].y;
    int x2 = tri.points[1].x;
    int y2 = tri.points[1].y;
    int x3 = tri.points[2].x;
    int y3 = tri.points[2].y;

    bool swapped;
    do {
        swapped = false;
        if (y1 > y2) {
            intSwap(&y1,&y2);
            intSwap(&x1,&x2);
            swapped = true;
        }
        if (y2 > y3) {
            intSwap(&y2, &y3);
            intSwap(&x2, &x3);
            swapped = true;
        }
    } while (swapped);
    if (y3 == y1) {
        return;
    }
    if (y1==y2) {
        fillFlatTop(x1,y1,x2,y2,x3,y3,color);
    } else if (y2==y3) {
        fillFlatBottom(x2,y2,x3,y3,x1,y1,color);
    } else {
        int my = y2;
        int mx = (float)(x3-x1)*(y2-y1)/(float)(y3-y1)+x1;
        fillFlatBottom(x2,y2,mx,my,x1,y1,color);
        fillFlatTop(x2,y2,mx,my,x3,y3,color);
    }
}
vec3 barycentric(vec2 a, vec2 b, vec2 c, vec2 p) {
    vec2 ab = vec2Subtract(b,a);
    vec2 ac = vec2Subtract(c,a);
    vec2 pc = vec2Subtract(c,p);
    vec2 pb = vec2Subtract(b,p);
    vec2 ap = vec2Subtract(p,a);
    float totalParalellogram = vec2Cross(ac,ab);
    if (totalParalellogram < 0) totalParalellogram *= -1;
    float alpha = vec2Cross(pc,pb) / totalParalellogram;
    if (alpha < 0) alpha *= -1;
    float beta = vec2Cross(ac,ap) / totalParalellogram;
    if (beta < 0) beta *= -1;
    float gamma = 1 - alpha - beta;
    return (vec3){alpha,beta,gamma};
}
void drawTexel(vec2 a, vec2 b, vec2 c, vec2 a_uv, vec2 b_uv, vec2 c_uv, int x, int y, Color *texture) {
    vec3 weights = barycentric(a,b,c,(vec2){x,y});
    if (weights.x > 1 || weights.y > 1 || weights.z > 1) drawPixel(x,y,BLACK);

    float u = a_uv.x*weights.x + b_uv.x*weights.y + c_uv.x*weights.z;
    float v = a_uv.y*weights.x + b_uv.y*weights.y + c_uv.y*weights.z;

    if (u > 1 || v > 1) {
        // printf("%f,%f\n",u,v);
        // printf("%f %f %f, %f %f %f, %f %f %f\n", weights.x, weights.y, weights.z, a_uv.x, b_uv.x, c_uv.x, a_uv.y, b_uv.y, c_uv.y);
    }
    float uDiff = u - 1;
    float vDiff = v - 1;
    if (uDiff > 0.1 || vDiff > 0.1) {
        // printf("-----------\n");
        // printf("%f,%f\n",u,v);
        // printf("%f %f %f, %f %f %f, %f %f %f\n", weights.x, weights.y, weights.z, a_uv.x, b_uv.x, c_uv.x, a_uv.y, b_uv.y, c_uv.y);
        // printf("-----------\n");
    }

    int u_loc = abs((int)(u * textureWidth));
    int v_loc = abs((int)(v * textureHeight));

    int ind = u_loc * textureWidth + v_loc;

    if (ind > 4096) {
        ind = 4095;
    }

    drawPixel(x,y,meshTexture[ind]);
}
void textureTriangle(triangle tri, Color *texture) {
    int x1 = tri.points[0].x;
    int y1 = tri.points[0].y;
    int x2 = tri.points[1].x;
    int y2 = tri.points[1].y;
    int x3 = tri.points[2].x;
    int y3 = tri.points[2].y;
    float u1 = tri.texturePoints[0].x;
    float v1 = tri.texturePoints[0].y;
    float u2 = tri.texturePoints[1].x;
    float v2 = tri.texturePoints[1].y;
    float u3 = tri.texturePoints[2].x;
    float v3 = tri.texturePoints[2].y;

    //sort coordinates in ascending order of y
    if (y1 > y2) {
        intSwap(&x1,&x2);
        intSwap(&y1,&y2);
        floatSwap(&u1,&u2);
        floatSwap(&v1,&v2);
    }
    if (y2 > y3) {
        intSwap(&x2,&x3);
        intSwap(&y2,&y3);
        floatSwap(&u2,&u3);
        floatSwap(&v2,&v3);
    }
    if (y1 > y2) {
        intSwap(&x1,&x2);
        intSwap(&y1,&y2);
        floatSwap(&u1,&u2);
        floatSwap(&v1,&v2);
    }
    //render the top half, flat bottom part of the triangle
    float slopeOne = 0;
    float slopeTwo = 0;


    if (y2-y1 != 0) {
        slopeOne = (float)(x2-x1)/(y2-y1);
    }
    if (y3-y1 != 0) {
        slopeTwo = (float)(x3-x1)/(y3-y1);
    }

    float xStart = x1;
    float xEnd = x1;
    for (int y = y1; y <= y2; y++) {
        int l = round(xStart);
        int r = round(xEnd);
        if (l > r) {
            intSwap(&l,&r);
        }
        for (int x = l; x <= r; x++) {
            drawTexel((vec2){x1,y1},(vec2){x2,y2},(vec2){x3,y3},
                      (vec2){u1,v1},(vec2){u2,v2},(vec2){u3,v3},x,y,texture);
        }
        xStart += slopeOne;
        xEnd += slopeTwo;
    }
    if (y3-y2 != 0) {
        slopeOne = (float)(x3-x2)/(y3-y2);
    }
    xStart = x2;
    for (int y = y2+1; y <= y3; y++) {
        int l = round(xStart);
        int r = round(xEnd);
        if (l > r) {
            intSwap(&l,&r);
        }
        for (int x = l; x <= r; x++) {
            drawTexel((vec2){x1,y1},(vec2){x2,y2},(vec2){x3,y3},
                      (vec2){u1,v1},(vec2){u2,v2},(vec2){u3,v3},x,y,texture);
        }
        xStart += slopeOne;
        xEnd += slopeTwo;
    }
}
void drawRectangle(int xStart, int yStart, int width, int height, Color color) {
    //draw horizontal lines to create rect
    for (int y = yStart; y <= yStart+height; y++) {
        for (int x = xStart; x <= xStart+width; x++) {
            drawPixel(x,y,color);
        }
    }
}
