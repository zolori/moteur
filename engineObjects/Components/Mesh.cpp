#include "Mesh.h"

Mesh::Mesh(VertexAssembly* Vertices, std::vector<Texture*> Textures)
{
	vertices = Vertices;
	textures = Textures;

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

int Mesh::Draw()
{
	for (size_t i = 0; i < textures.size(); i++)
		textures[i]->useIMG(i);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, vertices->GetIndices().size(), GL_UNSIGNED_INT, 0);
	return vertices->GetIndices().size();
}

glm::mat4 Mesh::TransformMatrix(btRigidBody* rb)
{
	btTransform t;
	rb->getMotionState()->getWorldTransform(t);
	float mat[16];
	glm::mat4 transformMatrix;
	t.getOrigin();
	t.getRotation();
	t.getOpenGLMatrix(glm::value_ptr(transformMatrix));
	return transformMatrix;
}

glm::quat Mesh::Rotation(btRigidBody* rb)
{
	glm::quat quaternion = glm::quat(rb->getCenterOfMassTransform().getRotation().w(),
										rb->getCenterOfMassTransform().getRotation().x(),
										rb->getCenterOfMassTransform().getRotation().y(),
										rb->getCenterOfMassTransform().getRotation().z()
	);
	return quaternion;
}

glm::vec3 Mesh::Translation(btRigidBody* rb)
{
	glm::vec3 vector3 = glm::vec3(rb->getCenterOfMassTransform().getOrigin().x(),
									rb->getCenterOfMassTransform().getOrigin().y(),
									rb->getCenterOfMassTransform().getOrigin().z()
	);
	return vector3;
}


void Mesh::DrawSphere()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS, vertices->GetIndices().size(), GL_UNSIGNED_INT, 0);
}

void Mesh::DrawPlane()
{
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
