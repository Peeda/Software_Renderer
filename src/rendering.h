#ifndef RENDERING_H
#define RENDERING_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <raylib.h>

#include "vectors.h"

//RGBA
extern Color *colorBuffer;
extern Texture bufferTexture;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

void setupRendering();
void destroyRendering();
void resetBuffer(Color color);
void CPURender();
void textureRender();
//takes RGBA format for color
void drawPixel(int x, int y, Color color);
void drawGrid();
void drawRectangle(int xStart, int yStart, int width, int height, Color color);

#endif
