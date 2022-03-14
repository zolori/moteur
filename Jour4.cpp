#include "projet.h"

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
        glVertexPointer(3, GL_FLOAT, 0, g_vertex_buffer_data);

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
