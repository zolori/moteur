#pragma once
#include "Component.h"
#include "Header.h"
class Transform : public Component
{
public:
	/**
	* Constructor of the Transform class, derived from the abstract class Component
	* 
	* @param Position The position of the object. By default vec3(0.0f, 0.0f, 0.0f)
	* @param Rotation The rotation of the object. By default vec3(0.0f, 0.0f, 0.0f)
	* @param Scale The scale of the object. By default vec3(1.0f, 1.0f, 1.0f)
	*/
	Transform(glm::vec3 Position = glm::vec3(0.0f), glm::vec3 Rotation = glm::vec3(0.0f), glm::vec3 Scale = glm::vec3(1.0f));
	//Destructor of the Transform class
	~Transform();
	//Position getter
	inline glm::vec3 GetPosition() { return position; };
	//Rotation getter
	inline glm::vec3 GetRotation() { return rotation; };
	//Scale getter
	inline glm::vec3 GetScale() { return scale; };
	//Position setter
	inline void SetPosition(glm::vec3 newPosition) { position = newPosition; };
	//Rotation setter
	inline void SetRotation(glm::vec3 newRotation) { rotation = newRotation; };
	//Scale setter
	inline void SetScale(glm::vec3 newScale) { scale = newScale; };

	//Pure virtual method of Component overriden
	inline void f() override { printf("virtual function overriden"); }
private:
	//Attribute
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

