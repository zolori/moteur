#pragma once
#include "AssimpImporter.h"
#include "Mesh.h"
#include "VertexAssembly.h"

const aiScene* DoTheImport(const char* pFile)
{
    const aiScene* scene = aiImportFile(pFile,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);
    //if the import failed, stop function
    if (nullptr != scene) 
    {
        return scene;
    }
    else
    {
        return nullptr;
    }
}

Mesh* SceneProcessing(aiScene const* scene)
{
    Mesh* DrawnMesh;
    for (size_t i = 0; i < scene->mNumMeshes; i++)
    {
        std::vector<GLfloat> Pos;
        for (size_t j = 0; j < scene->mMeshes[i]->mNumVertices; j++)
        {
            Pos.push_back(scene->mMeshes[i]->mVertices[j].x);
            Pos.push_back(scene->mMeshes[i]->mVertices[j].y);
            Pos.push_back(scene->mMeshes[i]->mVertices[j].z);
        }
        

        std::vector<GLfloat> Norm;

        for (size_t j = 0; j < scene->mMeshes[i]->mNumVertices; j++)
        {
            Norm.push_back(scene->mMeshes[i]->mNormals[j].x);
            Norm.push_back(scene->mMeshes[i]->mNormals[j].y);
            Norm.push_back(scene->mMeshes[i]->mNormals[j].z);
        }

        std::vector<GLfloat> TexCoords;
        if (scene->mMeshes[i]->HasTextureCoords(0))
        {
            TexCoords.push_back(scene->mMeshes[i]->mTextureCoords[0]->x);
            TexCoords.push_back(scene->mMeshes[i]->mTextureCoords[0]->y);
        }
        VertexAssembly* MeshVertices = new VertexAssembly(Pos,
                                                          Norm,
                                                          TexCoords);
        std::vector<unsigned int> Indices;
        for (size_t j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
        {
            for (size_t g = 0; g < scene->mMeshes[i]->mFaces[j].mNumIndices; g++)
            {
                Indices.push_back(scene->mMeshes[i]->mFaces[j].mIndices[g]);
            }
        }
        DrawnMesh = new Mesh(MeshVertices, Indices);
    }
    return DrawnMesh;
}


