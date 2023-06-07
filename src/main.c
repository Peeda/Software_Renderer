#include "rendering.h"

void render();
void process_input();
void update();

int main() {
    setupRendering();
    while (!WindowShouldClose()) {
        process_input();
        update();
        render();
    }
    destroyRendering();
    return 0;
}
void process_input() {

}
void update() {

}
void render() {
    resetBuffer(0xFFFFFFFF);
    drawRectangle(200,200,500,500,0xFFFF00FF);
    drawRectangle(300,300,500,500,0x22FF33FF);
    CPURender();
}
