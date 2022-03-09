#include "projet.h"

int main(int argc, char* argv[]) {
	
    //jour1(argc, argv);
    //jour2(argc, argv);
    jour3(argc, argv);

	printf("Hello world");
	return 0;
}

void jour1(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    SDL_Window* win = SDL_CreateWindow("Moteur",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        windowsFlags);

    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);

    bool appRunning = true;
    while (appRunning) {
        SDL_Event currEvent;
        while (SDL_PollEvent(&currEvent)) {

        }
        glViewport(0, 0, 1024, 768);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(-0.5, 0.5, 0.0);
        glVertex3f(0.0, 0.0, 0.0);

        glEnd();

        SDL_GL_SwapWindow(win);
    }
}


void jour2(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    SDL_Window* win = SDL_CreateWindow("Moteur",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        windowsFlags);

    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);

    auto prevTime = steady_clock::now();

    bool appRunning = true;
    while (appRunning)
    {
        SDL_Event curEvent;
        while (SDL_PollEvent(&curEvent))
        {
        }

        glViewport(0, 0, 1024, 768);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);


        const float radius = 0.5;

        auto curTime = steady_clock::now();
        duration<float> fTime = curTime - prevTime;
        float camX = sin(fTime.count()) * radius;
        float camZ = cos(fTime.count()) * radius;

        vec3 cameraPos = vec3(camX, 1.0, camZ);
        vec3 cameraTarget = vec3(0.0, 0.0, 0.0);

        // Creation de la camera
        mat4 view;
        view = lookAt(cameraPos, //Position de la camera
            cameraTarget, //Cible à regarder
            vec3(0.0, 1.0, 0.0)); //position vertical

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(&view[0][0]);

        // Creation d'un triangle
        glColor4f(0.0, 1.0, 0.0, 1.0);
        glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);

        glEnd();

        // Creation d'un autre triangle
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glBegin(GL_TRIANGLES);
        glVertex3f(0.0, 0.0, -1.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 1.0);

        glEnd();

        SDL_GL_SwapWindow(win);
    }
}

void jour3(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    SDL_Window* win = SDL_CreateWindow("Moteur",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        windowsFlags);

    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);

    auto beginTime = steady_clock::now();
    auto prevTime = steady_clock::now();

    bool appRunning = true;
    while (appRunning)
    {
        SDL_Event curEvent;
        while (SDL_PollEvent(&curEvent))
        {
        }

        glViewport(0, 0, 1024, 768);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);


        const float radius = 2;

        auto curTime = steady_clock::now();
        duration<float> fTime = curTime - beginTime;
        float camX = sin(fTime.count()) * radius;
        float camZ = cos(fTime.count()) * radius;

        vec3 cameraTarget = vec3(0.0, 1.0, -2.0);
        vec3 cameraPos = cameraTarget - vec3(camX, 0.0, camZ);//vec3(camX, 1.0, camZ);

        // Creation de la camera
        mat4 view;
        view = lookAt(
            cameraPos,          //Position de la camera
            cameraTarget,       //Cible à regarder
            vec3(0.0, 1.0, 0.0) //position vertical
        );

        /* FragColor;

        vec3 lightColor(1.0f, 1.0f, 1.0f);
        vec3 objectColor(0.0f, 0.0f, 1.0f);

        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;

        vec3 result = ambient * objectColor;
        FragColor = vec4(result, 1.0);*/

        glMatrixMode(GL_PROJECTION);
        auto projMat = glm::frustum<float>(-1.024, 0.768, -1.024, 0.768, 1.0, 100.0);
        glLoadMatrixf(glm::value_ptr(projMat));

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(view));

        glTranslatef(0.0, 0.0, -2.0);

        glBegin(GL_QUADS);
        // top
        glColor3f(1.0f, 0.0f, 0.0f);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);

        glEnd();

        glBegin(GL_QUADS);
        // front
        glColor3f(0.0f, 1.0f, 0.0f);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);

        glEnd();

        glBegin(GL_QUADS);
        // right
        glColor3f(0.0f, 0.0f, 1.0f);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);

        glEnd();

        glBegin(GL_QUADS);
        // left
        glColor3f(0.0f, 0.0f, 0.5f);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);

        glEnd();

        glBegin(GL_QUADS);
        // bottom
        glColor3f(0.5f, 0.0f, 0.0f);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);

        glEnd();

        glBegin(GL_QUADS);
        // back
        glColor3f(0.0f, 0.5f, 0.0f);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);

        glEnd();


        SDL_GL_SwapWindow(win);
    }
}