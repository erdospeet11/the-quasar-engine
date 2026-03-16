#include "Window.hpp"
#include <iostream>

namespace engine{
    Window::Window(int w, int h) : width(w), height(h), m_handle(nullptr), gl_context(nullptr), is_Running(true) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        m_handle = SDL_CreateWindow("Quasar Engine", w, h, SDL_WINDOW_OPENGL);
        if(!m_handle) {
            std::cerr << "Window Error: " << SDL_GetError() << std::endl;
        }

        gl_context = SDL_GL_CreateContext(m_handle);
        if(!gl_context) {
            std::cerr << "Context Error: " << SDL_GetError() << std::endl;
        }
        
        SDL_GL_MakeCurrent(m_handle, gl_context);

        int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
        if (!version) {
            std::cerr << "GLAD Load Error" << std::endl;
        }
    }

    Window::~Window(){
        if(gl_context) SDL_GL_DestroyContext(gl_context);
        if (m_handle) {
            SDL_DestroyWindow(m_handle);
            m_handle = nullptr;
        }
    }

    bool Window::pollEvent(SDL_Event& event){
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                is_Running = false;
            }
            return true;
        }
        return false;
    }

    bool Window::isOpen(){
        return is_Running;
    }

    void Window::swapBuffers(){
        SDL_GL_SwapWindow(m_handle);
    }

    SDL_Window* Window::getHandle(){
        return m_handle;
    }

    SDL_GLContext Window::getContext(){
        return gl_context;
    }
}
