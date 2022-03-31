#pragma once
#include "../../common/Header.h"
class VertexAssembly
{
public:
	/**
	* Constructor of the VertexAssembly class
	* 
	* @param Position A vector containing all the positions (X Y Z)
	* @param Normal A vector containing all the normals (X Y Z)
	* @param Texcoord A vector containg all the texture coordinates (U V)
	* @param Color A vector containing all the color(R G B)
	*/
	VertexAssembly(std::vector<GLfloat> Position, 
					std::vector<unsigned int> Indices,
					std::vector<GLfloat> Normal = std::vector<GLfloat>(),
					std::vector<GLfloat> Texcoords =  std::vector<GLfloat>(),
					std::vector<GLfloat> Color = std::vector<GLfloat>());
	//Empty VertexAssembly constructor to be used by default
	VertexAssembly() = default;
	//Destructor of the VertexAssembly class
	~VertexAssembly();
	//Position getter
	inline std::vector<GLfloat> GetPosition() { return position; }
	//Normal getter
	inline std::vector<GLfloat> GetNormal() { return normal; }
	//Texcoord getter
	inline std::vector<GLfloat> GetTexCoords() { return texcoords; }
	//Color getter
	inline std::vector<GLfloat> GetColor() { return color; }
	//Indices getter
	inline std::vector<unsigned int> GetIndices() { return indices; }
private:
	//Attribute;

	std::vector<GLfloat> position;
	std::vector<GLfloat> normal;
	std::vector<GLfloat> texcoords;
	std::vector<GLfloat> color;

	std::vector<unsigned int> indices;
};

