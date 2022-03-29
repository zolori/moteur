#pragma once
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../engineObjects/Components/Mesh.h"
#include <vector>

struct Material
{
	glm::vec4 color;
};

struct Model
{
	Mesh* m_Mesh;
	Material* m_Mat;
};

struct ImportResult
{
	std::vector<Model> m_Models;
};

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
* @param scene The scene that you received after using DoTheImport.
* @param textureFile The textureFile name, can be left empty if no texture exist.
* @return An instance of the Mesh class with all the attribute necessary to be drawn by OpenGL
*/
std::vector<Mesh*> SceneProcessing(const aiScene* scene, const char* textureFile = nullptr);