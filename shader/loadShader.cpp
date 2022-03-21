//Glew
#include <GL/glew.h>

//Miscellaneous
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <SDL.h>
#include <vector>
#include "loadShader.hpp"
#include <filesystem>


namespace
{
#ifdef WIN32
	char exePath[MAX_PATH + 1] = { 0 };
#else
	char exePath[512] = { 0 };
#endif

	std::string_view exePathView;
}

GLuint FindShaders(const char* directory, const char* vertexShaderFN, const char* fragmentShaderFN)
{
	std::filesystem::path appPath(GetAppPath());
	auto appDir = appPath.parent_path();
	std::cout << appDir << std::endl;
	auto shaderPath = appDir / directory ;
	auto vShaderPath = shaderPath / vertexShaderFN;
	auto fShaderPath = shaderPath / fragmentShaderFN;
	std::string StringSShaderPath{ vShaderPath.u8string() };
	std::string StringFShaderPath{ fShaderPath.u8string() };

	GLuint programID = LoadShaders(StringSShaderPath.c_str(), StringFShaderPath.c_str());
	return programID;
}

std::string_view GetAppPath()
{
	if (exePath[0] == 0)
	{
#ifdef WIN32
		HMODULE exeModule = GetModuleHandleA(nullptr);
		if (exeModule == nullptr)
		{
			std::cout << "exeModule has failed" << std::endl;
		}
		uint32_t length = GetModuleFileNameA(exeModule, exePath, MAX_PATH);

		for (uint32_t i = 0; i < length; ++i)
		{
			if (exePath[i] == '\\')
			{
				exePath[i] = '/';
			}
		}
		exePathView = std::string_view(exePath, length);
#else
		ssize_t len = ::readlink("/proc/self/exe", exePath, sizeof(exePath) - 1);
		if (len != -1)
		{
			exePath[len] = '\0';
			char* posBack = strrchr(exePath, '/');
			exePathView = std::string_view(exePath, len);
			chdir(exePathView.begin());
		}
#endif
	}

	return exePathView;
}

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}