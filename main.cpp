#include "common/AssimpImporter.h"
#include <iostream>
#include "engineObjects/Components/Camera.h"
#include "common/functions.hpp"
#include "common/Header.h"
#include "engineObjects/Components/Light.hpp"
#include "common/Program.hpp"
#include "engineObjects/CoreClasses/BulletPhysics.h"
#include "engineObjects/CoreClasses/SolidSphere.h"
#include "engineObjects/Object.h"
#include "engineObjects/CoreClasses/VertexAssembly.h"


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
    //Light Setup
    std::vector<Light*> objectLights;
    Light* light1 = new Light("light1", vec3(-1.0, 5.0, 2.0), vec3(1.0, 0.0, 1.0), 50.0f);
    Light* light2 = new Light("light2",vec3(0.0, 5.0, 2.0), vec3(0.5, 1.0, 1.0), 100.0f);
    Light* light3 = new Light("light3", vec3(-2.0, 4.0, 2.0), vec3(0.25, 0.75, 0), 70.0f);
    Light* light4 = new Light("light4", vec3(2, 5, 2), vec3(0.15, 1, 0.65), 100.0f);
    Light* light5 = new Light("light5", vec3(-2, 5, 2), vec3(1, .45, 0.35), 50.0f);
    Light* light6 = new Light("light6", vec3(2, 5, 2), vec3(0.5, .56, .89), 100.0f);
    const char* lights[6]{};
    objectLights.push_back(light1);
    objectLights.push_back(light2);
    objectLights.push_back(light3);
    objectLights.push_back(light4);
    objectLights.push_back(light5);
    objectLights.push_back(light6);

    for (int i = 0; i < objectLights.size(); i++)
    {
        lights[i] = objectLights[i]->GetName();
    }

    Program prog1 = Program(SHADER_DIRECTORY, VERTEX_SHADER, FRAGMENT_SHADER, objectLights.size());
    std::string texture_path = FindFile("assets", "Bob_Blue.png");
    GLuint Texture = loadDDS(texture_path.c_str());
    prog1.AddUniformVar("myTextureSampler");

    //Mesh To Draw Setup
    std::vector<Mesh*> MeshesToBeDrawn;
    std::string mesh_path = FindFile("assets", "Bob.fbx");
    const aiScene* scene = DoTheImport(mesh_path.c_str());
    if (scene != nullptr)
    {
        MeshesToBeDrawn = SceneProcessing(scene);
    }
  

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 
    //Camera Setup
    Camera cam = Camera(win);
    int x, y;
    bool Freelook = true;

    glEnable(GL_CULL_FACE);
    //DeltaTime Setup
    auto beginTime = steady_clock::now();
    auto prevTime = steady_clock::now();

    int index = 0;
    bool isActive = true;
    float newLightPower = 0.0f;
    vec3 newLightPosition = vec3(0.0, 0.0, 0.0);
    float currentLightColor[3]{};


    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 base_pos = viewport->Pos;

    DeltaTime Time;

    std::vector<Object*> GameObjects;
    float xPos = 0;
    float yPos = 5;
    float zPos = 0;
    float sphereRadius = .5f;

    BulletPhysics* PhysicsEngine = new BulletPhysics();

    for (size_t i = 0; i < 10; i++)
    {
        if (i == 0)
        {
            //Create a plane object of name Plane
            Object* planeObject = new Object("Plane");
            //Create the plane in a physic way
            PhysicsEngine->CreatePlane();
            //Parameter for the render of the plane
            std::vector<GLfloat> Vertices = {
                -1000,0,1000,
                -1000,0,-1000,
                1000,0,-1000,
                1000,0,1000
            };
            std::vector<GLfloat> TexCoord = {
                -1000,0,1000,
                -1000,0,-1000,
                1000,0,-1000,
                1000,0,1000
            };
            std::vector<unsigned int> Indices = {
                0, 1, 2,
                0, 2, 3
            };
            VertexAssembly* planeVertexAssembly = new VertexAssembly(Vertices, Vertices, TexCoord, Indices, Vertices);
            //Create the Mesh
            Mesh* planeMesh = new Mesh(planeVertexAssembly);
            //Add it to the planeObject
            planeObject->AddComponent(planeMesh);
            GameObjects.push_back(planeObject);
        }
        else
        {
            //Create a sphere object of name Spherei
            Object* sphereObject = new Object("Sphere%d" + i);
            //Create the sphere in a physic way
            PhysicsEngine->CreateSphere(sphereRadius, xPos + i, yPos, zPos + i, 1.0f);
            //Create the parameter for the render of the sphere
            SolidSphere* sphereParameter = new SolidSphere(sphereRadius, 12, 24);
            //Add them to a VertexAssembly
            VertexAssembly* sphereVertexAssembly = new VertexAssembly(sphereParameter->GetVertices(), sphereParameter->GetNormals(), sphereParameter->GetTexcoords(), sphereParameter->GetIndices(), sphereParameter->GetVertices());
            //Create the Mesh with the parameter from the VertexAssembly and indices from 
            Mesh* sphereMesh = new Mesh(sphereVertexAssembly);
            //add it to the sphereObject
            sphereObject->AddComponent(sphereMesh);
            //Put the sphere object in the vector housing all of them
            GameObjects.push_back(sphereObject);
        }
    }
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
                        case SDLK_LALT:
                            Freelook = false;
                            break;
                        case SDLK_SPACE:
                        {
                            //Create a sphere object of name Sphere
                            Object* sphereObject = new Object("Sphere");
                            //Create the sphere in a physic way
                            PhysicsEngine->CreateSphere(sphereRadius, cam.GetPosition().x, cam.GetPosition().y, cam.GetPosition().z, 1.0f);
                            btVector3 look = btVector3(cam.GetFront().x, cam.GetFront().y, cam.GetFront().z) * 20;
                            PhysicsEngine->rigidbodies.back()->setLinearVelocity(look);
                            //Create the parameter for the render of the sphere
                            SolidSphere* sphereParameter = new SolidSphere(sphereRadius, 12, 24);
                            //Add them to a VertexAssembly
                            VertexAssembly* sphereVertexAssembly = new VertexAssembly(sphereParameter->GetVertices(), sphereParameter->GetNormals(), sphereParameter->GetTexcoords(), sphereParameter->GetIndices(), sphereParameter->GetVertices());
                            //Create the Mesh with the parameter from the VertexAssembly and indices from 
                            Mesh* sphereMesh = new Mesh(sphereVertexAssembly);
                            //add it to the sphereObject
                            sphereObject->AddComponent(sphereMesh);
                            //Put the sphere object in the vector housing all of them
                            GameObjects.push_back(sphereObject);
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (curEvent.key.keysym.sym)
                    {
                        case SDLK_LALT:
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

        glClearColor(0.0, 0.0, 0.4f, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.SetView();
        cam.SetProjection();

        for (size_t i = 0; i < GameObjects.size(); i++)
        {
            glm::mat4 Model = glm::mat4(1.0f);
            Mesh* MeshComponent = (Mesh*)GameObjects[i]->GetSpecificComponent(ComponentName::MESH_COMPONENT);
            glm::vec3 translationVector = vec3(MeshComponent->TransformMatrix(PhysicsEngine->rigidbodies[i])[3].x,
            MeshComponent->TransformMatrix(PhysicsEngine->rigidbodies[i])[3].y,
            MeshComponent->TransformMatrix(PhysicsEngine->rigidbodies[i])[3].z);
            Model = glm::translate(Model, translationVector);
            glm::mat4 MVP = cam.GetProjection() * cam.GetView() * Model;
            prog1.UpdateCamera(&MVP[0][0], &Model[0][0], &cam.GetView()[0][0]);

            if (PhysicsEngine->rigidbodies[i]->getCollisionShape()->getShapeType() == STATIC_PLANE_PROXYTYPE)
            {
                MeshComponent->DrawPlane();
            }
            else
            {
                MeshComponent->DrawSphere();
            }
        }

        prog1.Use();
        prog1.BindTexture(Texture);
        prog1.UpdateLights(objectLights);
        

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

        //Gravity Window
        static float sliderFloat = -10.f;
        ImGui::Begin("Tools");
        ImGui::SliderFloat("Gravity", &sliderFloat, -20.f, 20.f);
        ImGui::End();

        PhysicsEngine->SetGravity(sliderFloat);
        prevTime = curTime;

        //Rendering end
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(win);
        PhysicsEngine->Update(elapsedSeconds.count());
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    PhysicsEngine->~BulletPhysics();
    for (size_t i = 0; i < GameObjects.size(); i++)
    {
        Mesh* MeshComponent = (Mesh*)GameObjects[i]->GetSpecificComponent(ComponentName::MESH_COMPONENT);
        MeshComponent->~Mesh();
    }
    //delete scene;
    return 0;
}
