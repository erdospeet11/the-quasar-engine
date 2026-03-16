#pragma once
#include <glad/gl.h>
#include <SDL3/SDL.h>

namespace engine{
    class Window{
        private:
            SDL_Window* m_handle;
            SDL_GLContext gl_context;
            int height;
            int width;
            bool is_Running;
        public:
            Window(int w, int h);
            ~Window();
            void pollEvents();
            bool isOpen();
            void swapBuffers();
            SDL_Window* getHandle();
    };
}