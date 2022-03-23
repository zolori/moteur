#include "common/AssimpImporter.h"
#include <iostream>
#include "engineObjects/Components/Camera.h"
#include "common/functions.hpp"
#include "common/Header.h"

#define SDL_WIDTH 1024
#define SDL_HEIGHT 728

using namespace std;
using namespace glm;


SDL_Window* SetUpWindow()
{
    SDL_Window* win;
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    win = SDL_CreateWindow("Engine",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WIDTH,
        SDL_HEIGHT,
        windowsFlags);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);
    glewInit();
    return win;
}

int main(int argc, char* argv[])
{   
    SDL_Window* win = SetUpWindow();
    SDL_bool apprunning = SDL_TRUE;

    glewInit();

    std::string vertex_file_path = FindFile("shader", "SimpleVertexShader.vertexshader");
    std::string  fragment_file_path = FindFile("shader", "SimpleFragmentShader.fragmentshader");

    GLuint programID = LoadShaders(vertex_file_path.c_str(), fragment_file_path.c_str());

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    std::vector<Mesh*> MeshesToBeDrawn;
    std::string mesh_path = FindFile("assets", "Bob.fbx");
    const aiScene* scene = DoTheImport(mesh_path.c_str());
    if (scene != nullptr)
    {
        MeshesToBeDrawn = SceneProcessing(scene);
    }
  

    //Camera Setup
    Camera cam = Camera(win);
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    int x, y;
    glEnable(GL_CULL_FACE);
    struct DeltaTime Time;
    SDL_ShowCursor(SDL_DISABLE);


    while (apprunning)
    {
        float deltaTime = Time.GetDeltaTime();

        SDL_Event curEvent;
        while (SDL_PollEvent(&curEvent))
        {
            switch(curEvent.type)
            {
                case SDL_KEYDOWN:

                    switch (curEvent.key.keysym.sym)
                    {
                        case SDLK_DOWN:
                            cam.CameraInputKey(CameraMovement::DOWN, deltaTime);
                            break;

                        case SDLK_UP:
                            cam.CameraInputKey(CameraMovement::UP, deltaTime);
                            break;

                        case SDLK_LEFT:
                            cam.CameraInputKey(CameraMovement::LEFT, deltaTime);
                            break;

                        case SDLK_RIGHT:
                            cam.CameraInputKey(CameraMovement::RIGHT, deltaTime);
                            break;
                        case SDLK_ESCAPE:
                            apprunning = SDL_FALSE;
                        default:
                            break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    x = curEvent.motion.xrel;
                    y = curEvent.motion.yrel;
                    cam.CameraInputMouse(x, y, deltaTime);
                    break;

                case SDL_MOUSEWHEEL:
                    cam.CameraInputScroll(curEvent.wheel.preciseY);
                    break;

                case SDL_QUIT:
                    apprunning = SDL_FALSE;
                    break;

                default:
                    break;
            }
        }

        cam.ResetMousePosition();
        glClearColor(0.0, 0.0, 0.4f, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        glUseProgram(programID);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &cam.GetMVP()[0][0]);

        for (size_t i = 0; i < MeshesToBeDrawn.size(); i++)
        {
            MeshesToBeDrawn[i]->Draw();
        }
        SDL_GL_SwapWindow(win);
    }
    delete scene;
    return 0;
}
