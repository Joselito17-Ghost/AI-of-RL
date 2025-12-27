#include <SDL3/SDL.h>
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#include "env/grid_env.h"
#include "rl/qlearning.h"
#include "rl/trainer.h"

int main(int, char**) {
    // ===============================
    // SDL INIT
    // ===============================
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "AI Training Env",
        800, 600,
        SDL_WINDOW_RESIZABLE
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    // ===============================
    // IMGUI INIT
    // ===============================
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // ===============================
    // RL OBJECTS
    // ===============================
    GridEnv env(5, 5);
    QLearning agent(25, 4);
    Trainer trainer(env, agent);

    bool running = true;
    bool training_done = false;

    SDL_Event e;

    // ===============================
    // MAIN LOOP
    // ===============================
    while (running) {
        while (SDL_PollEvent(&e)) {
            ImGui_ImplSDL3_ProcessEvent(&e);
            if (e.type == SDL_EVENT_QUIT)
                running = false;
        }

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // ===============================
        // UI
        // ===============================
        ImGui::Begin("AI Training");

        if (ImGui::Button("Train (1000 episodes)")) {
            trainer.train(1000);
            trainer.saveRewardsCSV("training_rewards.csv");
            training_done = true;
        }

        if (training_done) {
            ImGui::Text("Training finished!");
        }

        ImGui::End();

        // ===============================
        // RENDER
        // ===============================
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    // ===============================
    // CLEANUP
    // ===============================
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
