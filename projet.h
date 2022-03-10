#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SDL.h>

#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

#include "gc_3d_defs.hpp"


using namespace glm;
using namespace std::chrono;

void jour1(int argc, char* argv[]);
void jour2(int argc, char* argv[]);
void jour3(int argc, char* argv[]);
void jour4(int argc, char* argv[]);
void initClear();
mat4 initCamera(steady_clock::time_point beginTime);
void initProjection(mat4 view);
void lights();