#pragma once
#include <string_view>
#include <chrono>
#include "Header.h"
#include <filesystem>

using Clock = std::chrono::high_resolution_clock;
using Timestamp = Clock::time_point;
using Duration = Clock::duration;


struct DeltaTime {
    Timestamp currentTime;
    Timestamp lastTime;
    float deltaTime;
    Duration duration;
    float GetDeltaTime();
    std::chrono::duration<float> GetDuration();
};

std::string FindFile(const char* directory, const char* name);
SDL_Window* SetUpWindow();
GLuint loadDDS(const char* imagepath);
std::string_view GetAppPath();
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
ImGuiIO& initApp(SDL_Window* win);

void DisplayUniform(GLuint program);