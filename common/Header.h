#pragma once
//Glew
#include <GL/glew.h>

//Windows
#ifdef _WIN32
#include <windows.h>
#endif

//SDL
#include <SDL.h>
#include <gl/GL.h>

//GLM
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

//Miscellaneous
#include <vector>
#include <chrono>
using namespace std::chrono;

//Imgui
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"