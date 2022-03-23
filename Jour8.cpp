#include "projet.h"

void loadModel() {
    SDL_Init(SDL_INIT_VIDEO);
    uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    SDL_Window* win = SDL_CreateWindow("Moteur",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        windowsFlags);

    ImGuiIO& io = initApp(win);
    glewInit();

    GLuint programID = LoadShaders("../../PMoteur/moteur/J8Vshader.vertexshader", "../../PMoteur/moteur/J8Fshader.fragmentshader");

    filesystem::path appPath(GetAppPath());
    auto appDir = appPath.parent_path();
    auto shaderPath = appDir / "Ressources";
    auto vShaderPath = shaderPath / "defaultVertexShader.glsl";
    auto fShaderPath = shaderPath / "defaultFragmentShader.glsl";

    bool appRunning = true;
    while (appRunning) {
        SDL_Event currEvent;
        while (SDL_PollEvent(&currEvent)) {

        }
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

        // Read our .obj file
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        bool res = loadOBJ("../../PMoteur/Ressources/Obj/wooden crate", vertices, uvs, normals);

        printf("res = %s", res);

        GLuint normalbuffer;
        glGenBuffers(1, &normalbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
            2,                                // attribute
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );
    }
}