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
	Mesh(VertexAssembly* Vertices, Texture* Texture = new Texture());
	//Destructor of the Mesh class
	~Mesh();
	//Get Rotations
	glm::quat Rotation(btRigidBody* rb);
	//Get Translation
	glm::vec3 Translation(btRigidBody* rb);
	//Calculate the transformMatrix of a plane
	//Draw a sphere;
	int DrawSphere();
	//Draw a plane;
	int DrawPlane();
	//Attribute
	VertexAssembly* vertices;
	Texture* texture;

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

