#pragma once
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

/**
* Import the object in a scene
* 
* @param pFile Path to the object
* @return A const aiScene with all the values from the object
*/
const aiScene* DoTheImport(const char* pFile);

/**
* Process the scene while creating instance of the Mesh class
* 
* @param scene The scene that you received after using DoTheImport
* @return An instance of the Mesh class with all the attribute necessary to be drawed by OpenGL
*/
Mesh* SceneProcessing(const aiScene* scene);