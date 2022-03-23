#include "Mesh.h"

Mesh::Mesh(VertexAssembly* Vertices, std::vector<unsigned int> Indices, std::vector<Texture*> Textures)
{
	vertices = Vertices;
	indices = Indices;
	textures = Textures;

	name = ComponentName::MESH_COMPONENT;

	setupMesh();
}

Mesh::~Mesh()
{
	PosBuffer->DisableBuffer();
	NormBuffer->DisableBuffer();
	TexcoordBuffer->DisableBuffer();
	delete PosBuffer;
	delete NormBuffer;
	delete TexcoordBuffer;
	delete IndiceBuffer;
}

void Mesh::Draw()
{

	for (size_t i = 0; i < textures.size(); i++)
	{
		textures[i]->useIMG(i);
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	PosBuffer = new Buffer(vertices->GetPosition(), 0, 3, GL_ARRAY_BUFFER);
	NormBuffer = new Buffer(vertices->GetNormal(), 1, 3, GL_ARRAY_BUFFER);
	TexcoordBuffer = new Buffer(vertices->GetTexCoords(), 2, 2, GL_ARRAY_BUFFER);

	PosBuffer->BindBuffer();
	NormBuffer->BindBuffer();
	TexcoordBuffer->BindBuffer();

	IndiceBuffer = new IndicesBuffer(indices, GL_ELEMENT_ARRAY_BUFFER);
}
