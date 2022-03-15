#include "projet.h"

#include <glm/gtx/transform.hpp>

void cubeTexture() {
    SDL_Init(SDL_INIT_VIDEO);
    uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    SDL_Window* win = SDL_CreateWindow("Moteur",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        windowsFlags);

    initApp(win);

    glewInit();

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders("../../PMoteur/moteur/SimpleVertexShader.vertexshader", "../../PMoteur/moteur/SimpleFragmentShader.fragmentshader");

    auto beginTime = steady_clock::now();
    auto prevTime = steady_clock::now();

    bool appRunning = true;
    while (appRunning)
    {
        SDL_Event curEvent;
        while (SDL_PollEvent(&curEvent)) {}

        glUseProgram(programID);
        initClear();

        mat4 ViewMatrix = translate(mat4(), vec3(-3.0f, 0.0f, 0.0f));
        // Camera matrix
        mat4 View = glm::lookAt(
            glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
        // Generates a really hard-to-read matrix, but a normal, standard 4x4 matrix nonetheless
        mat4 Projection = perspective(radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f);
        mat4 Model = mat4(1.0f);
        mat4 mvp = Projection * View * Model;

        // Get a handle for our "MVP" uniform
        // Only during the initialisation
        GLuint MatrixID = glGetUniformLocation(programID, "MVP");

        // Send our transformation to the currently bound shader, in the "MVP" uniform
        // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        initProjection(View);
        //lights();

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

        //initBuffer(g_vertex_buffer_data);
        GLuint vertexbuffer;
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
        glDisableVertexAttribArray(0);

        GLuint Texture = loadBMP_custom("image.bmp");
        
        SDL_GL_SwapWindow(win);
    }
}