#include "Mesh.h"

Mesh::Mesh(VertexAssembly* Vertices, Texture* Texture)
{
	vertices = Vertices;
	texture = Texture;

	name = ComponentName::MESH_COMPONENT;

	setupMesh();
}

Mesh::~Mesh()
{
	PosBuffer->DisableBuffer();
	NormBuffer->DisableBuffer();
	TexcoordBuffer->DisableBuffer();
	ColorBuffer->DisableBuffer();
	delete PosBuffer;
	delete NormBuffer;
	delete TexcoordBuffer;
	delete IndiceBuffer;
}


glm::mat4 Mesh::TransformMatrix(btRigidBody* rb)
{
	float r = ((btSphereShape*)rb->getCollisionShape())->getRadius();
	btTransform t;
	rb->getMotionState()->getWorldTransform(t);
	float mat[16];
	glm::mat4 transformMatrix;
	t.getOpenGLMatrix(glm::value_ptr(transformMatrix));
	return transformMatrix;
}

void Mesh::DrawSphere()
{
	texture->useIMG(0);
	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS, vertices->GetIndices().size(), GL_UNSIGNED_INT, 0);
}

void Mesh::DrawPlane()
{
	texture->useIMG(0);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, vertices->GetIndices().size(), GL_UNSIGNED_INT, 0);
}



void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	PosBuffer = new Buffer(vertices->GetPosition(), 0, 3);
	NormBuffer = new Buffer(vertices->GetNormal(), 1, 3);
	TexcoordBuffer = new Buffer(vertices->GetTexCoords(), 2, 2);
	ColorBuffer = new Buffer(vertices->GetColor(), 3, 3);

	PosBuffer->BindBuffer();
	NormBuffer->BindBuffer();
	TexcoordBuffer->BindBuffer();
	ColorBuffer->BindBuffer();

	IndiceBuffer = new IndicesBuffer(vertices->GetIndices());
}
