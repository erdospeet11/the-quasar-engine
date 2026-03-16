#pragma once
#include <SDL3/SDL.h>
#include <vector>

namespace engine {
    class Input {
    public:
        static void init();
        static void update();

        static bool isKeyHeld(SDL_Scancode key);
        static bool isKeyPressed(SDL_Scancode key);
        static bool isKeyReleased(SDL_Scancode key);

        static bool isMouseButtonHeld(int button);
        static bool isMouseButtonPressed(int button);
        static bool isMouseButtonReleased(int button);

        static float getMouseX();
        static float getMouseY();

    private:
        static const bool* currentKeyStates;
        static std::vector<bool> previousKeyStates;

        static Uint32 previousMouseState;
    };
}
