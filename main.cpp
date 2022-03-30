#include "common/AssimpImporter.h"
#include <iostream>
#include "engineObjects/Components/Camera.h"
#include "common/functions.hpp"
#include "common/Header.h"
#include "engineObjects/CoreClasses/BulletPhysics.h"
#include "engineObjects/CoreClasses/SolidSphere.h"
#include "engineObjects/Object.h"
#include "engineObjects/CoreClasses/VertexAssembly.h"

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

	auto beginTime = steady_clock::now();
	auto prevTime = steady_clock::now();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Camera Setup
	Camera cam = Camera(win);
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	int x, y;
	//glEnable(GL_CULL_FACE);
	DeltaTime Time;
	//SDL_ShowCursor(SDL_DISABLE);
	int var = 0;
	int nbBall = 0;

	bool Freelook = true;
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
			nbBall++;
		}
	}
	while (apprunning)
	{
		float deltaTime = Time.GetDeltaTime();

		SDL_Event curEvent;
		while (SDL_PollEvent(&curEvent))
		{
			ImGui_ImplSDL2_ProcessEvent(&curEvent);
			switch (curEvent.type)
			{
			case SDL_KEYDOWN:

				switch (curEvent.key.keysym.sym)
				{
				case SDLK_s:
				case SDLK_DOWN:
					cam.CameraInputKey(CameraMovement::DOWN, deltaTime);
					break;

				case SDLK_z:
				case SDLK_UP:
					cam.CameraInputKey(CameraMovement::UP, deltaTime);
					break;

				case SDLK_q:
				case SDLK_LEFT:
					cam.CameraInputKey(CameraMovement::LEFT, deltaTime);
					break;

				case SDLK_d:
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
					nbBall++;
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

		cam.SetView();
		cam.SetProjection();

		glUseProgram(programID);;

		for (size_t i = 0; i < GameObjects.size(); i++)
		{

			Mesh* MeshComponent = (Mesh*)GameObjects[i]->GetSpecificComponent(ComponentName::MESH_COMPONENT);
			glm::mat4 Model = glm::mat4(1.0f);
			glm::vec3 translationVector = vec3(MeshComponent->TransformMatrix(PhysicsEngine->rigidbodies[i])[3].x,
				MeshComponent->TransformMatrix(PhysicsEngine->rigidbodies[i])[3].y,
				MeshComponent->TransformMatrix(PhysicsEngine->rigidbodies[i])[3].z);
			Model = glm::translate(Model, translationVector);
			glm::mat4 MVP = cam.GetProjection() * cam.GetView() * Model;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
			if (PhysicsEngine->rigidbodies[i]->getCollisionShape()->getShapeType() == STATIC_PLANE_PROXYTYPE)
			{
				var += MeshComponent->DrawPlane();
			}
			else
			{
				var += MeshComponent->DrawSphere();
			}
		}

		//Render Loop
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(win);

		ImGui::NewFrame();
		// Draw some widgets

		auto curTime = steady_clock::now();
		duration<float> elapsedSeconds = curTime - prevTime;


		ImGui::Begin("Perfs");
		ImGui::LabelText(" : Frame Time (ms)", "%f"" : Frame Time (ms)", elapsedSeconds.count() * 1e-3);
		ImGui::LabelText(" : FPS", "%f", 1.0 / elapsedSeconds.count());
		ImGui::End();

		static float sliderFloat = -10.f;
		ImGui::Begin("Tools");
		ImGui::LabelText(" : Triangles", "%d", var);
		ImGui::LabelText(" : Nb de BOULE", "%d", nbBall);
		ImGui::SliderFloat("Gravity", &sliderFloat, -50.f, 30.f);
		ImGui::End();

		PhysicsEngine->SetGravity(sliderFloat);

		prevTime = curTime;

		//Rendering end
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		var = 0;

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
