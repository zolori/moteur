#include "projet.h"

void initClear() {
    glViewport(0, 0, 1024, 768);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
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
{/*
    vec4 FragColor;

    vec3 lightColor(1.0f, 1.0f, 1.0f);
    vec3 objectColor(0.0f, 0.0f, 1.0f);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);*/
}


void initBuffer(const GLfloat g_vertex_buffer_data[]) {

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
}