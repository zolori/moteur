#pragma once
#include "AssimpImporter.h"
#include "../../engineObjects/Components/Mesh.h"
#include "../engineObjects/CoreClasses/VertexAssembly.h"
#include "functions.hpp"

const aiScene* DoTheImport(const char* pFile)
{
    const aiScene* scene = aiImportFile(pFile,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType |
        aiProcess_FlipUVs);
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

std::vector<Mesh*> SceneProcessing(aiScene const* scene, const char* textureFile)
{
    std::vector<Mesh*> MeshesToDraw;
    for (size_t i = 0; i < scene->mNumMeshes; i++)
    {
        Mesh* MeshToDraw;
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
            for (size_t j = 0; j < scene->mMeshes[i]->mNumVertices; j++)
            {
                TexCoords.push_back(scene->mMeshes[i]->mTextureCoords[0][j].x);
                TexCoords.push_back(scene->mMeshes[i]->mTextureCoords[0][j].y);
            }
        }
        if (scene->HasMaterials())
        {

        }
        std::vector<GLfloat> Color;
        if (scene->mMeshes[i]->HasVertexColors(0))
        {
            for (size_t j = 0; j < scene->mMeshes[i]->mNumVertices; j++)
            {
                Color.push_back(scene->mMeshes[i]->mColors[0][j].r);
                Color.push_back(scene->mMeshes[i]->mColors[0][j].g);
                Color.push_back(scene->mMeshes[i]->mColors[0][j].b);
                printf("Red: %f\n", scene->mMeshes[i]->mColors[0][j].r);
                printf("Green: %f\n", scene->mMeshes[i]->mColors[0][j].g);
                printf("Blue: %f\n", scene->mMeshes[i]->mColors[0][j].b);
            }
        }

        std::vector<unsigned int> Indices;
        for (size_t j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
        {
            for (size_t g = 0; g < scene->mMeshes[i]->mFaces[j].mNumIndices; g++)
            {
                Indices.push_back(scene->mMeshes[i]->mFaces[j].mIndices[g]);
            }
        }
        VertexAssembly* MeshVertices = new VertexAssembly(Pos,
            Norm,
            TexCoords,
            Indices,
            Color);
        Texture* texture;
        //std::vector<Texture*> TextureVector;
        if (scene->HasTextures())
        {
            for (size_t j = 0; j < scene->mNumTextures; j++)
            {
                texture = new Texture(scene->mTextures[i]->mWidth, scene->mTextures[i]->mHeight);
                //TextureVector.push_back(texture);
            }
        }
        else
        {
            if (textureFile != nullptr)
            {
                texture = new Texture();
                std::string texure_path = FindFile("assets", textureFile);
                texture->loadIMG(texure_path.c_str());
                //TextureVector.push_back(texture);
            }
        }

        MeshToDraw = new Mesh(MeshVertices, texture);
        //MeshesToDraw.push_back(MeshToDraw);
    }
    return MeshesToDraw;
}


