#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "engine/Window.hpp"
#include "engine/Renderer.hpp"
#include "engine/Input.hpp"
#include "engine/Model.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>

using namespace engine;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main() {
    Window window = Window(SCREEN_WIDTH, SCREEN_HEIGHT);
    Renderer renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(window.getHandle(), window.getContext());
    ImGui_ImplOpenGL3_Init("#version 430 core");

    engine::Input::init();

    bool showImGui = true;

    while(window.isOpen()){
        engine::Input::update();

        SDL_Event event;
        while (window.pollEvent(event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
        }

        if (engine::Input::isKeyPressed(SDL_SCANCODE_F1)) {
            showImGui = !showImGui;
        }
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        if (showImGui) {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT));
            //ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.6f, 0.0f, 0.0f, 1.0f));
            ImGui::Begin("Debug & Monitoring", nullptr, window_flags);
            ImGui::Text("Monitoring Panel");
            ImGui::Separator();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            
            ImGui::Separator();
            ImGui::Text("Input Subsystem:");
            ImGui::Text("Mouse Position: (%.1f, %.1f)", engine::Input::getMouseX(), engine::Input::getMouseY());
            
            if (engine::Input::isMouseButtonHeld(SDL_BUTTON_LEFT)) {
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Left Mouse Button Submitting!");
            }
            
            if (engine::Input::isKeyHeld(SDL_SCANCODE_SPACE)) {
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "SPACE Held!");
            }

            if (engine::Input::isKeyPressed(SDL_SCANCODE_E)) {
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "E Key was pressed!");
            }
            ImGui::End();
            ImGui::PopStyleColor();
        }

        renderer.clear();
        
        glm::mat4 transform = glm::mat4(1.0f);
        //float timeValue = SDL_GetTicks() / 1000.0f;
        //transform = glm::rotate(transform, timeValue * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::scale(transform, glm::vec3(1.0f));
        
        static engine::Model* importedModel = nullptr;
        static bool attemptedLoad = false;
        
        if (!attemptedLoad) {
            std::string modelPath = std::string(GAME_SOURCE_DIR) + "models/test-scene.glb";
            importedModel = new engine::Model(modelPath); 
            attemptedLoad = true;
        }

        if (importedModel && !importedModel->meshes.empty()) {
            renderer.renderModel(*importedModel, transform);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        window.swapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    return 0;
}