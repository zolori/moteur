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

#include <ctime>
#include <ratio>
#include <chrono>
#include <filesystem>

#include "gc_3d_defs.hpp"

#include <string_view>
#if WIN32
#include <Windows.h>
#endif

#include "IndicesBuffer.h"
#include "AssimpImporter.h"
#include "shader/loadShader.hpp"
#include "Camera.h"

#define SDL_WIDTH 1024
#define SDL_HEIGHT 728

using namespace std;
using namespace glm;
using namespace GC_3D;

namespace
{
	#ifdef WIN32
		char exePath[MAX_PATH + 1] = { 0 };
	#else
		char exePath[512] = { 0 };
	#endif
		std::string_view exePathView;
}

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
ImGuiIO& initApp(SDL_Window* win);
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
void cubeTexture();
//GLuint loadBMP_custom(const char* imagepath);
bool loadOBJ(const char* path, vector < vec3 >& out_vertices, vector < vec2 >& out_uvs, vector < vec3 >& out_normals);
void loadModel();
string_view GetAppPath();


