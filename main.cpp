#include "common/AssimpImporter.h"
#include <iostream>
#include "engineObjects/Components/Camera.h"
#include "common/functions.hpp"
#include "common/Header.h"
#include "engineObjects/Components/Light.hpp"
#include "common/Program.hpp"

#define SDL_WIDTH 1024
#define SDL_HEIGHT 728
#define SHADER_DIRECTORY "shader"
#define VERTEX_SHADER "SimpleVertexShader.vertexshader"
#define FRAGMENT_SHADER "SimpleFragmentShader.fragmentshader"

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
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //Light Setup
    std::vector<Light*> objectLights;
    Light* light1 = new Light("light1", vec3(1.0, 5.0, 2.0), vec3(1.0, 0.0, 1.0), 50.0f);
    Light* light2 = new Light("light2",vec3(0.0, 5.0, 2.0), vec3(0.5, 1.0, 1.0), 100.0f);
    Light* light3 = new Light("light3", vec3(-1.0, 5.0, 2.0), vec3(0.25, 0.75, 0), 70.0f);
    /*Light* light4 = new Light("light4", vec3(2, 5, 2), vec3(0.15, 1, 0.65), 100.0f);
    Light* light5 = new Light("light5", vec3(-2, 5, 2), vec3(1, .45, 0.35), 50.0f);
    Light* light6 = new Light("light6", vec3(2, 5, 2), vec3(0.5, .56, .89), 100.0f);*/
    const char* lights[3]{};
    objectLights.push_back(light1);
    objectLights.push_back(light2);
    objectLights.push_back(light3);
    /*objectLights.push_back(light4);
    objectLights.push_back(light5);
    objectLights.push_back(light6);*/

    for (int i = 0; i < 3; i++)
    {
        lights[i] = objectLights[i]->GetName();
    }


    Program prog1 = Program(SHADER_DIRECTORY, VERTEX_SHADER, FRAGMENT_SHADER,3);

    //Mesh To Draw Setup
    std::vector<Mesh*> MeshesToBeDrawn;
    std::string mesh_path = FindFile("assets", "Bob.fbx");
    const aiScene* scene = DoTheImport(mesh_path.c_str());
    if (scene != nullptr)
    {
        MeshesToBeDrawn = SceneProcessing(scene);
    }
    
    //Camera Setup
    Camera cam = Camera(win);
    int x, y;
    bool Freelook = false;

    glEnable(GL_CULL_FACE);
    //DeltaTime Setup
    struct DeltaTime Time;
    auto beginTime = steady_clock::now();
    auto prevTime = steady_clock::now();

    std::string texture_path = FindFile("assets", "Bob_Blue.png");
    GLuint Texture = loadDDS(texture_path.c_str());
    prog1.AddUniformVar("myTextureSampler");

    int index = 0;
    bool isActive = true;
    float newLightPower = 0.0f;
    vec3 newLightPosition = vec3(0.0, 0.0, 0.0);
    float currentLightColor[3]{};


    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 base_pos = viewport->Pos;

    while (apprunning)
    {
        glClearColor(0.0, 0.0, 0.4f, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
                            Freelook = true;
                            break;

                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (curEvent.key.keysym.sym)
                    {
                        case SDLK_LCTRL:
                            Freelook = false;
                        break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (Freelook)
                    {
                        x = curEvent.motion.xrel;
                        y = curEvent.motion.yrel;
                        cam.CameraInputMouse(x, y, deltaTime);
                    }
                    break;

                case SDL_MOUSEWHEEL:
                    if (Freelook)
                    {
                        cam.CameraInputScroll(curEvent.wheel.preciseY);
                    }
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


        prog1.Use();
        prog1.UpdateCamera(&cam.GetMVP()[0][0], &cam.GetModel()[0][0], &cam.GetView()[0][0]);
        prog1.BindTexture(Texture);
        prog1.UpdateLights(objectLights);


       // DisplayUniform(prog1.GetNum());

        for (size_t i = 0; i < MeshesToBeDrawn.size(); i++)
        {
            MeshesToBeDrawn[i]->Draw();
        }
        

        //Render Loop
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(win);

        ImGui::NewFrame();
        // Draw some widgets
        
        auto curTime = steady_clock::now();
        duration<float> elapsedSeconds = curTime - prevTime;

  
        //Perfs Window
        ImGui::SetNextWindowPos(ImVec2(base_pos.x + 100, base_pos.y + 100), ImGuiCond_FirstUseEver);
        ImGui::Begin("Perfs");
        ImGui::Text("Frame Time (ms) : ", "");
        ImGui::LabelText("","%f", elapsedSeconds.count() * 1e-3);
        ImGui::Text("FPS : ", "");
        ImGui::LabelText("", "%f", 1.0 / elapsedSeconds.count());
        ImGui::End();


      
        //Light Window
        ImGui::SetNextWindowPos(ImVec2(base_pos.x +10, base_pos.y + 125), ImGuiCond_Always);
        ImGui::Begin("Lights");
        ImGui::Combo("Lights", &index, lights, IM_ARRAYSIZE(lights));
        ImGui::BeginChild("Selected light Parameters", ImVec2(0.0,0.0), true, ImGuiWindowFlags_None);
        //Light general info
        ImGui::Text("%s", lights[index]);
        isActive = objectLights[index]->GetActive();
        ImGui::Checkbox("Active", &isActive);
        objectLights[index]->SetActive(isActive);

        //Light Parameters
        ImGui::Text("Parameters", "");
        if (isActive)
        {
            //Update light position
            newLightPosition = objectLights[index]->GetLightPosition();
            ImGui::SliderFloat("Light Position X", &newLightPosition.x, -15.0f, 15.0f);
            ImGui::SliderFloat("Light Position Y", &newLightPosition.y, -15.0f, 15.0f);
            ImGui::SliderFloat("Light Position Z", &newLightPosition.z, -15.0f, 15.0f);
            objectLights[index]->SetLightPosition(newLightPosition);
            ImGui::Separator();

            //Update light Color
            currentLightColor[0] = objectLights[index]->GetLightColor().x;
            currentLightColor[1] = objectLights[index]->GetLightColor().y;
            currentLightColor[2] = objectLights[index]->GetLightColor().z;
            ImGui::ColorEdit3("Light Color", currentLightColor, 0);
            ImGui::Separator();
            objectLights[index]->SetLightColor(vec3(currentLightColor[0], currentLightColor[1], currentLightColor[2]));

            //Update light power
            newLightPower = objectLights[index]->GetLightPower();
            ImGui::SliderFloat("Light Power", &newLightPower, 1.0f, 100.0f);
            objectLights[index]->SetLightPower(newLightPower);

        }
        ImGui::EndChild();
        ImGui::End();


        prevTime = curTime;

        //Rendering end
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(win);
    }
    //delete scene;
    return 0;
}
