#pragma once
#include "../Component.h"
#include "../CoreClasses/Texture.h"
#include "../CoreClasses/VertexAssembly.h"
#include "../CoreClasses/IndicesBuffer.h"
#include "../CoreClasses/BulletPhysics.h"

#include <vector>
class Mesh : public Component
{
public:
	/**
	* Constructor of the Mesh class derived from the abstract class Component
	* Automatically call the setupMesh function after the value are initialized
	* 
	* @param Vertices An instance of the Vertex class filled with all the positions, normals and texcoords of the*
	* mesh
	* @param Indices A vector filled with the necessary indices to build the mesh
	* @param A vector filled with instances of the Texture class containing the mesh textures.
	* By default empty
	*/
	Mesh(VertexAssembly* Vertices, std::vector<Texture*> Textures = std::vector<Texture*>());
	//Destructor of the Mesh class
	~Mesh();
	/**
	* Draw the elements of the mesh
	*/
	int Draw();
	//Calculate the transformMatrix of a sphere
	glm::mat4 TransformMatrix(btRigidBody* rb);
	//Calculate the transformMatrix of a plane
	//Draw a sphere;
	int DrawSphere();
	//Draw a plane;
	int DrawPlane();
	//Attribute
	VertexAssembly* vertices;
	std::vector<Texture*> textures;

	//Pure virtual method of Component overriden
	inline void f() override { printf("virtual function overriden"); }

private:
	//Render data
	unsigned int VAO;

	Buffer* PosBuffer;
	Buffer* NormBuffer;
	Buffer* TexcoordBuffer;
	Buffer* ColorBuffer;
	IndicesBuffer* IndiceBuffer;
	/**
	* Setup the VAO buffer as well as the Position, Normal, TextureCoordinate and Indice buffer
	*/
	void setupMesh();
};

