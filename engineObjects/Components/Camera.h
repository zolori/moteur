#pragma once
#include "../Component.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <chrono>
#include <SDL_opengl.h>
#include <SDL.h>

using namespace glm;

enum class CameraMovement {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Camera : Component {
	//GLuint IDCam;
	SDL_Window* win;

	vec3 Up;
	vec3 Right;
	vec3 WorldUp;
	float Yaw = -90.0f;
	float Pitch = 0.0f;
	float axe = -1.0f;

	mat4 Projection;
	mat4 View;
	mat4 Model = glm::mat4(1.0f);
	mat4 MVP;

	float Fov;
	float FovMini = 10.0f;
	float FovMax = 100.0f;
	float FovAmmount = 2.0f;

	float RatioWidth;
	float RatioHeight;
	float NearClipping;
	float FarClipping;

	// camera options
	float MouseSensitivity = 0.1f;
	float Zoom;

public:
	vec3 Position;
	vec3 Front;
	float MovementSpeed = 30.0f;

	//Constructors
	Camera(SDL_Window* NewWin);
	void f();
	//Others
	void CameraInputKey(CameraMovement DIR, float deltaTime);
	void CameraInputMouse(int x, int y, float deltaTime);
	void InvertAxe();
	void CameraInputScroll(float wheelPos);
	//Setters
	void SetRight();
	void SetUp();
	void SetFront();
	void ResetMousePosition();
	void SetProjectionParameters(float NewFov, float NewRatioWidth, float NewRatioHeight, float NewNearClipping, float NewFarClipping);
	void SetProjection();
	void SetView();
	void SetMVP();
	//Getters
	vec3 GetPosition();
	vec3 GetRight();
	vec3 GetFront();
	mat4 GetMVP();
};