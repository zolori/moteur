#include "common/AssimpImporter.h"
#include <iostream>
#include "engineObjects/Components/Camera.h"
#include "common/functions.hpp"
#include "common/Header.h"
#include "engineObjects/CoreClasses/BulletPhysics.h"
#include "engineObjects/CoreClasses/SolidSphere.h"

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

    ImGuiIO& io = initApp(win);
    glewInit();

    std::string vertex_file_path = FindFile("shader", "SimpleVertexShader.vertexshader");
    std::string  fragment_file_path = FindFile("shader", "SimpleFragmentShader.fragmentshader");

    GLuint programID = LoadShaders(vertex_file_path.c_str(), fragment_file_path.c_str());

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    std::vector<Mesh*> MeshesToBeDrawn;
    std::string mesh_path = FindFile("assets", "Pool.fbx");
    const aiScene* scene = DoTheImport(mesh_path.c_str());
    if (scene != nullptr)
    {
        MeshesToBeDrawn = SceneProcessing(scene);
    }
    
    GLuint VAO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    BulletPhysics* PhysicsEngine = new BulletPhysics();

    float cubeWidth = 1.0f;
    float cubeHeight = 1.0f;
    float cubeDepth = 1.0f;

    std::vector<float> cubePosBufferData = {
        cubeWidth, cubeHeight, cubeDepth,
        -cubeWidth, cubeHeight, cubeDepth,
        cubeWidth, -cubeHeight, cubeDepth,
        -cubeWidth, -cubeHeight, cubeDepth,
        cubeWidth, cubeHeight, -cubeDepth,
        -cubeWidth, cubeHeight, -cubeDepth,
        cubeWidth, -cubeHeight, -cubeDepth,
        -cubeWidth, -cubeHeight, -cubeDepth,
    };

    Buffer* cubeBufferPos = new Buffer(cubePosBufferData, 0, 3);
    cubeBufferPos->BindBuffer();
    PhysicsEngine->CreateBox(cubeWidth, cubeHeight, cubeDepth, cubeWidth, cubeHeight, cubeDepth, 0.1f);

    std::vector<unsigned int> cubeIndiceBufferData = {
        0,1,2,
        3,2,1,
        4,0,6,
        6,0,2,
        5,1,4,
        4,1,0,
        7,3,1,
        7,1,5,
        5,4,7,
        7,4,6,
        7,2,3,
        7,6,2
    };

    IndicesBuffer* cubeBufferIndices = new IndicesBuffer(cubeIndiceBufferData);
    

    SolidSphere sphere(1, 12, 24);
    //Camera Setup
    Camera cam = Camera(win);
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    int x, y;

    struct DeltaTime Time;
    SDL_ShowCursor(SDL_DISABLE);

    auto beginTime = steady_clock::now();
    auto prevTime = steady_clock::now();
    int var = 0;
    int* drawCallCount = &var;

    bool Freelook = true;

    while (apprunning)
    {
        float deltaTime = Time.GetDeltaTime();
        
        SDL_Event curEvent;
        while (SDL_PollEvent(&curEvent))
        {
            ImGui_ImplSDL2_ProcessEvent(&curEvent);
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
                            break;

                        case SDLK_LCTRL:
                            Freelook = false;
                            break;

                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (curEvent.key.keysym.sym)
                    {
                        case SDLK_LCTRL:
                            Freelook = true;
                        break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (Freelook)
                    {
                        x = curEvent.motion.xrel;
                        y = curEvent.motion.yrel;
                        //printf("mouse position \n x : %d\n y: %d\n", x, y);
                        cam.CameraInputMouse(x, y, deltaTime);
                    }
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
        SDL_ShowCursor(!Freelook);

        if (Freelook)
        {
            cam.ResetMousePosition();
        }

        glClearColor(0.0, 0.0, 0.4f, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        glUseProgram(programID);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &cam.GetMVP()[0][0]);
        
        for (size_t i = 0; i < MeshesToBeDrawn.size(); i++)
        {
            var += MeshesToBeDrawn[i]->Draw();
        }

        var = var / 3;
        
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, cubeIndiceBufferData.size(), GL_UNSIGNED_INT, 0);
        PhysicsEngine->Update();

        sphere.Draw();

        //Render Loop
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(win);
        
        ImGui::NewFrame();
        // Draw some widgets

        auto curTime = steady_clock::now();
        duration<float> elapsedSeconds = curTime - prevTime;

        ImGui::Begin("Perfs");
        //ImGui::LabelText("Frame Time (ms) : ", "%f", elapsedSeconds.count() * 1e-3);
        ImGui::LabelText("Triangles : ", "%d", var);
        ImGui::LabelText("FPS : ", "%f", 1.0 / elapsedSeconds.count());
        ImGui::End();

        prevTime = curTime;

        //Rendering end
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        var = 0;

        SDL_GL_SwapWindow(win);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    //delete scene;
    return 0;
}
