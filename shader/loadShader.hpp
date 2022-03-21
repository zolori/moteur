#pragma once
#include <string_view>

GLuint FindShaders(const char* directory, const char* vertexShaderFN, const char* fragmentShaderFN);
std::string_view GetAppPath();
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);