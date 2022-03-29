#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include "Camera.h"
using namespace std::chrono;

Camera::Camera(SDL_Window* NewWin)
{
    Super:name = ComponentName::CAM_COMPONENT;
    Position = glm::vec3(1, 2, 5);
    Front = glm::vec3(0, 0, -1.0f);
    Up = glm::vec3(0, 1, 0);
    win = NewWin;
    SetProjectionParameters(45.0f, 1024, 728, 0.1f, 500.0f);
}

void Camera::f()
{

}

void Camera::CameraInputKey(CameraMovement DIR, float deltaTime)
{
    float CameraSpeed = deltaTime * MovementSpeed;

    switch (DIR)
    {
    case CameraMovement::UP:
        Position += Front * CameraSpeed;
        break;

    case CameraMovement::DOWN:
        Position -= Front * CameraSpeed;
        break;

    case CameraMovement::RIGHT:
        Position += glm::normalize(glm::cross(Front, Up)) * CameraSpeed;

        break;

    case CameraMovement::LEFT:
        Position -= glm::normalize(glm::cross(Front, Up)) * CameraSpeed;
        break;

    default:
        break;
    }
    //SetFront();
    std::cout << glm::to_string(Position) << std::endl;
}

void Camera::CameraInputMouse(int x, int y, float deltaTime)
{
    Yaw += (float)x * MouseSensitivity;
    Pitch += ((float)y * MouseSensitivity) * axe;

    if (Pitch > 89.0f)
    {
        Pitch = 89.0f;
    }

    if (Pitch < -89.0f)
    {
        Pitch = -89.0f;
    }
    this->SetFront();
}

void Camera::InvertAxe()
{
    axe * -1.0f;
}

void Camera::CameraInputScroll(float wheelPos)
{

    if ((Fov > FovMini && wheelPos > 0) || (Fov < FovMax && wheelPos < 0))
    {
        Fov -= FovAmmount * wheelPos;
        //std::cout <<  Fov << std::endl;
    }
}

void Camera::SetRight()
{
    Right = glm::vec3(sin(Yaw - 3.14f / 2.0f), 0, cos(Yaw - 3.14f / 2.0f));
}

void Camera::SetUp()
{
    Up = glm::cross(Right, Front);
}

void Camera::SetFront()
{
    Front = vec3();
    Front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front.y = sin(glm::radians(Pitch));
    Front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = normalize(Front);
}

void Camera::ResetMousePosition()
{
    SDL_WarpMouseInWindow(win, RatioWidth / 2, RatioHeight / 2);
}

void Camera::SetProjectionParameters(float NewFov, float NewRatioWidth, float NewRatioHeight, float NewNearClipping, float NewFarClipping)
{
    Fov = NewFov;
    RatioWidth = NewRatioWidth;
    RatioHeight = NewRatioHeight;
    NearClipping = NewNearClipping;
    FarClipping = NewFarClipping;
}

void Camera::SetProjection()
{
    Projection = glm::perspective(glm::radians(Fov), (float)RatioWidth / (float)RatioHeight, NearClipping, FarClipping);
}

void Camera::SetView()
{
    View = lookAt(Position, Position + Front, Up);
}
vec3 Camera::GetPosition()
{
    return Position;
}

vec3 Camera::GetRight()
{
    return Right;
}

vec3 Camera::GetFront()
{
    return Front;
}

mat4 Camera::GetProjection()
{
    return Projection;
}

mat4 Camera::GetView()
{
    return View;
}
