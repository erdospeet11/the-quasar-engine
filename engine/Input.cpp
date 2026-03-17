#include "Input.hpp"
#include <algorithm>

namespace engine {
    const bool* Input::currentKeyStates = nullptr;
    std::vector<bool> Input::previousKeyStates;
    Uint32 Input::previousMouseState = 0;

    void Input::init() {
        int numkeys = 0;
        currentKeyStates = SDL_GetKeyboardState(&numkeys);
        previousKeyStates.resize(numkeys, false);
        previousMouseState = SDL_GetMouseState(nullptr, nullptr);
    }

    void Input::update() {
        if (!currentKeyStates) return;

        int numkeys = 0;
        currentKeyStates = SDL_GetKeyboardState(&numkeys);
        if (previousKeyStates.size() != static_cast<size_t>(numkeys)) {
            previousKeyStates.resize(numkeys, false);
        }
        std::copy(currentKeyStates, currentKeyStates + numkeys, previousKeyStates.begin());

        previousMouseState = SDL_GetMouseState(nullptr, nullptr);
    }

    bool Input::isKeyHeld(SDL_Scancode key) {
        if (!currentKeyStates) return false;
        return currentKeyStates[key];
    }

    bool Input::isKeyPressed(SDL_Scancode key) {
        if (!currentKeyStates || key >= previousKeyStates.size()) return false;
        return currentKeyStates[key] && !previousKeyStates[key];
    }

    bool Input::isKeyReleased(SDL_Scancode key) {
        if (!currentKeyStates || key >= previousKeyStates.size()) return false;
        return !currentKeyStates[key] && previousKeyStates[key];
    }

    bool Input::isMouseButtonHeld(int button) {
        return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_MASK(button)) != 0;
    }

    bool Input::isMouseButtonPressed(int button) {
        Uint32 currentMouseState = SDL_GetMouseState(nullptr, nullptr);
        return ((currentMouseState & SDL_BUTTON_MASK(button)) != 0) && ((previousMouseState & SDL_BUTTON_MASK(button)) == 0);
    }

    bool Input::isMouseButtonReleased(int button) {
        Uint32 currentMouseState = SDL_GetMouseState(nullptr, nullptr);
        return ((currentMouseState & SDL_BUTTON_MASK(button)) == 0) && ((previousMouseState & SDL_BUTTON_MASK(button)) != 0);
    }

    float Input::getMouseX() {
        float x, y;
        SDL_GetMouseState(&x, &y);
        return x;
    }

    float Input::getMouseY() {
        float x, y;
        SDL_GetMouseState(&x, &y);
        return y;
    }
}
