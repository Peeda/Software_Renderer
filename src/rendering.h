#ifndef RENDERING_H
#define RENDERING_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <raylib.h>

#include "vectors.h"

typedef uint32_t u32;

//RGBA
extern u32 *colorBuffer;
extern Texture bufferTexture;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

void setupRendering();
void destroyRendering();
void resetBuffer(u32 color);
void CPURender();
void textureRender();
//takes RGBA format for color
void drawPixel(int x, int y, u32 color);
void drawGrid();
void drawRectangle(int xStart, int yStart, int width, int height, u32 color);

#endif
