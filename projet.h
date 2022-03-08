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


using namespace glm;
using namespace std::chrono;

void jour1(int argc, char* argv[]);
void jour2(int argc, char* argv[]);