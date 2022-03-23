#pragma once
#include <string_view>
#include <chrono>
#include "Header.h"
#include <filesystem>

using Clock = std::chrono::high_resolution_clock;
using Timestamp = Clock::time_point;
using Duration = Clock::duration;

//std::filesystem::path appPath;

struct DeltaTime {
    Timestamp currentTime;
    Timestamp lastTime;
    float deltaTime;
    Duration duration;
    float GetDeltaTime();
};

std::string FindFile(const char* directory, const char* name);
SDL_Window* SetUpWindow();
std::string_view GetAppPath();
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
ImGuiIO& initApp(SDL_Window* win);