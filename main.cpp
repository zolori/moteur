#include "IndicesBuffer.h"
#include "AssimpImporter.h"
#include "shader/loadShader.hpp"

using Time = std::chrono::steady_clock;
using ms = std::chrono::milliseconds;
using float_sec = std::chrono::duration<float>;
using float_time_point = std::chrono::time_point<Time, float_sec>;

float_time_point getCurrentTime();

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;


    SDL_Window* win = SDL_CreateWindow("Engine",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        windowsFlags);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);
    //SDL_SetRelativeMouseMode(SDL_TRUE);

    glewInit();

    auto startTime = getCurrentTime();

    GLuint programID = LoadShaders("C:/Users/abouffay/Documents/engine/shader/SimpleVertexShader.glsl", "C:/Users/abouffay/Documents/engine/shader/SimpleFragmentShader.glsl");

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    Mesh* ArrayOfMeshToBeDrawn[1];
    /*
    std::vector<GLfloat> g_vertex_cube_buffer_data = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    Buffer* CubeVertexBuffer = new Buffer(g_vertex_cube_buffer_data, 0, 3);

    std::vector<GLfloat> g_uv_cube_buffer_data = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };

    Buffer* CubeUVBuffer = new Buffer(g_uv_cube_buffer_data, 1, 2);
    */
    const aiScene* scene = DoTheImport("C:/Users/abouffay/Documents/GitHub/Husky.fbx");
    if (scene != nullptr)
    {
        Mesh* MeshToBeDrawn = SceneProcessing(scene);
        ArrayOfMeshToBeDrawn[0] = MeshToBeDrawn;
    }
   SDL_bool apprunning = SDL_TRUE;
    while (apprunning)
    {
        SDL_Event curEvent;
        while (SDL_PollEvent(&curEvent))
        {
            if (curEvent.type == SDL_QUIT)
            {
                apprunning = SDL_FALSE;
            }
            SDL_Delay(20);
        }

        glUseProgram(programID);

        ArrayOfMeshToBeDrawn[0]->Draw();

        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)1024 / (float)768, 0.1f, 100.0f);

        //mat4 Projection = ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);

        glm::mat4 View = glm::lookAt(
                            glm::vec3(4, 3, 3), //Camera is here
                            glm::vec3(0, 0, 0), //Camera looks here
                            glm::vec3(0, 1, 0) //Head is up (0, -1, 0) to look upside down
        );

        glm::mat4 ModelCube = glm::mat4(1.0f);

        glm::mat4 MVPCube = Projection * View * ModelCube; //Matrix Model View Projection

        GLuint MatrixID = glGetUniformLocation(programID, "MVP");

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, value_ptr(MVPCube));

        glViewport(0, 0, 1024, 768);
        glClearColor(0.0, 0.0, 0.4f, 0.0);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //CubeVertexBuffer->BindBuffer();

        //color cube buffer
        /*glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBufferCube);
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );*/

        //CubeUVBuffer->BindBuffer();

        //glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
        //Triangle matrix
        /*
        mat4 ModelTriangle = translate(identity<mat4>(), vec3(3.0f, 0, 0));

        mat4 MVPTriangle = Projection * View * ModelTriangle;

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, value_ptr(MVPTriangle));

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferTriangle);
        glVertexAttribPointer(
            2,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBufferTriangle);
        glVertexAttribPointer(
            3,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );

        glDrawArrays(GL_TRIANGLES, 0, 3);
        */
        //CubeVertexBuffer->DisableBuffer();
        //CubeUVBuffer->DisableBuffer();
        SDL_GL_SwapWindow(win);
    }
    //delete CubeVertexBuffer;
    //delete CubeUVBuffer;
    return 0;
}

float_time_point getCurrentTime()
{
    return Time::now();
}