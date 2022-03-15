#pragma once

#include <stdio.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>
#include <SDL.h>

#include "dep/imgui/imgui.h"
#include "dep/imgui/backends/imgui_impl_sdl.h"
#include "dep/imgui/backends/imgui_impl_opengl3.h"

#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

#include "gc_3d_defs.hpp"

using namespace glm;
using namespace std::chrono;
using namespace std;

// opengl ancient
void jour1(int argc, char* argv[]);
void jour2(int argc, char* argv[]);
void jour3(int argc, char* argv[]);
void jour4(int argc, char* argv[]);
void initClear();
mat4 initCamera(steady_clock::time_point beginTime);
void initProjection(mat4 view);
void lights();

// opengl recent
void jour5(int argc, char* argv[]);
void triangle();
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
void matrice();
void cube();
void initBuffer(const GLfloat g_vertex_buffer_data[]);
void initApp(SDL_Window* win);
