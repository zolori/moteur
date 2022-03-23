#pragma once
#include <string_view>
#include <chrono>
#include "Header.h"

using Clock = std::chrono::high_resolution_clock;
using Timestamp = Clock::time_point;
using Duration = Clock::duration;

struct DeltaTime {
    Timestamp currentTime;
    Timestamp lastTime;
    float deltaTime;
    Duration duration;
    float GetDeltaTime();
};

SDL_Window* SetUpWindow();

GLuint FindShaders(const char* directory, const char* vertexShaderFN, const char* fragmentShaderFN);
std::string_view GetAppPath();
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
ImGuiIO& initApp(SDL_Window* win);
