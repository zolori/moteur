#include "projet.h"

int main(int argc, char* argv[]) {
	
    //jour1(argc, argv);
    //jour2(argc, argv);
    //jour3(argc, argv);
    jour4(argc, argv);

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

        initClear();
        mat4 view = initCamera(beginTime);

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

void jour4(int argc, char* argv[]) {
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

        initClear();
        mat4 view = initCamera(beginTime);
        initProjection(view);
        lights();

        static const GLfloat g_vertex_buffer_data[] = {
            1.0f, 1.0f,-1.0f, // avant 1 0
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,  
            1.0f, 1.0f,-1.0f, // avant 2 3
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f, // gauche 1 6
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,  
            -1.0f,-1.0f,-1.0f, // gauche 2 9
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f, // dessous 1 12
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f,-1.0f, 1.0f, // dessous 2 15
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f, // droite 1 18
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f, // droite 2 21
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, // haut 1 24
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f, // haut 2 27
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // derrière 1 30
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, // derrière 2 33
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
        };
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3,GL_FLOAT,0, g_vertex_buffer_data);

        static GLubyte frontIndices1[] = { 0, 1, 2 };
        static GLubyte frontIndices2[] = { 3, 4, 5 };
        static GLubyte leftIndices1[] = { 6, 7, 8 };
        static GLubyte leftIndices2[] = { 9, 10, 11 };
        static GLubyte bottomIndices1[] = { 12, 13, 14 };
        static GLubyte bottomIndices2[] = { 15, 16, 17 };
        static GLubyte rightIndices1[] = { 18, 19, 20 };
        static GLubyte rightIndices2[] = { 21, 22, 23 };
        static GLubyte topIndices1[] = { 24, 25, 26 };
        static GLubyte topIndices2[] = { 27, 28, 29 };
        static GLubyte backIndices1[] = { 30, 31, 32 };
        static GLubyte backIndices2[] = { 33, 34, 35 };

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, frontIndices1);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, frontIndices2);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, leftIndices1);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, leftIndices2);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, bottomIndices1);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, bottomIndices2);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, rightIndices1);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, rightIndices2);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, topIndices1);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, topIndices2);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, backIndices1);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, backIndices2);

        SDL_GL_SwapWindow(win);
    }
}

void initClear() {
    glViewport(0, 0, 1024, 768);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

mat4 initCamera(steady_clock::time_point beginTime) {
    const float radius = 4;

    auto curTime = steady_clock::now();
    duration<float> fTime = curTime - beginTime;
    float camX = sin(fTime.count()) * radius;
    float camZ = cos(fTime.count()) * radius;

    vec3 cameraTarget = vec3(0.0, 1.0, -2.0);
    vec3 cameraPos = cameraTarget - vec3(camX, 0.0, camZ);//vec3(camX, 1.0, camZ);

    // Creation de la camera
    mat4 view;
    return view = lookAt(
        cameraPos,          //Position de la camera
        cameraTarget,       //Cible à regarder
        vec3(0.0, 1.0, 0.0) //position vertical
    );
}

void initProjection(mat4 view) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    auto projMat = glm::frustum<float>(-1.024, 0.768, -1.024, 0.768, 1.0, 100.0);
    glLoadMatrixf(glm::value_ptr(projMat));

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));

    glTranslatef(0, 1, -2);
}

void lights()
{
    vec4 FragColor;

    vec3 lightColor(1.0f, 1.0f, 1.0f);
    vec3 objectColor(0.0f, 0.0f, 1.0f);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);

}
