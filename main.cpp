#include "common/AssimpImporter.h"
#include <iostream>
#include "engineObjects/Components/Camera.h"
#include "common/functions.hpp"
#include "common/Header.h"
#include "engineObjects/Components/Light.hpp"

#define SDL_WIDTH 1024
#define SDL_HEIGHT 728
#define SHADER_DIRECTORY "shader"
#define VERTEX_SHADER "firstVertexShader.txt"
#define FRAGMENT_SHADER "firstFragmentShader.txt"

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

    //Shader Setup
    std::string vertex_file_path = FindFile("shader", "SimpleVertexShader.vertexshader");
    std::string  fragment_file_path = FindFile("shader", "SimpleFragmentShader.fragmentshader");

    GLuint programID = LoadShaders(vertex_file_path.c_str(), fragment_file_path.c_str());

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
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
    int x, y;
    bool Freelook = false;

    glEnable(GL_CULL_FACE);
    //DeltaTime Setup
    struct DeltaTime Time;
    auto beginTime = steady_clock::now();
    auto prevTime = steady_clock::now();

    //Light Setup
    std::string texture_path = FindFile("assets", "Bob_Blue.png");
    GLuint Texture = loadDDS(texture_path.c_str());
    GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

    const char* lights[2]{};
    Light* objectLights[2]{};
    int lightNumber = 0;
    Light* ltest = new Light(vec3(1, 5, 2), vec3(1, 0, 1), 50.0f);
    ltest->SetUniformVar(programID);
    ltest->SetName("light1");

    Light* ltest2 = new Light(vec3(0, 5, 2), vec3(1, 1, 1), 100.0f);
    ltest2->SetUniformVar(programID);
    ltest2->SetName("light2");

    lights[0] = ltest->GetName();
    lights[1] = ltest2->GetName();
    objectLights[0] = ltest;
    objectLights[1] = ltest2;


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

        std::string currentPt = "pointsLights[]";
        for (int i = 0; i < 2; i++)
        {
            std::string newPt = currentPt.insert(13, to_string(i));
            glUniform3fv(glGetUniformLocation(programID, (newPt + ".position").c_str()), 1, &objectLights[i]->GetLightPosition()[0]);
            glUniform3fv(glGetUniformLocation(programID, (newPt + ".LightParam_Color").c_str()), 1, &objectLights[i]->GetLightColor()[0]);
            glUniform1f(glGetUniformLocation(programID, (newPt + ".LightParam_Power").c_str()), objectLights[i]->GetLightPower());
        }

        glUseProgram(programID);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &cam.GetMVP()[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &cam.GetModel()[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &cam.GetView()[0][0]);

       /* ltest->UpdateLight();
        ltest->UpdateLight();*/


        /*for (int i = 0; i < 2; i++)
        {
            objectLights[i]->UpdateLight();
        }*/

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        glUniform1i(TextureID, 0);

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
