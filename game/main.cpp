#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "engine/Window.hpp"
#include "engine/Renderer.hpp"

using namespace engine;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main() {
    Window window = Window(SCREEN_WIDTH, SCREEN_HEIGHT);
    Renderer renderer;

    while(window.isOpen()){
        window.pollEvents();
        renderer.clear();
        renderer.renderCube();
        window.swapBuffers();
    }
    return 0;
}