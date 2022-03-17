#pragma once
#include "Component.h"
#include "Header.h"
class Transform : public Component
{
public:
	//Constructor
	Transform(glm::vec3 Position = glm::vec3(0.0f), glm::vec3 Rotation = glm::vec3(0.0f), glm::vec3 Scale = glm::vec3(1.0f));
	//Getter
	inline glm::vec3 GetPosition() { return position; };
	inline glm::vec3 GetRotation() { return rotation; };
	inline glm::vec3 GetScale() { return scale; };
	//Setter
	inline void SetPosition(glm::vec3 newPosition) { position = newPosition; };
	inline void SetRotation(glm::vec3 newRotation) { rotation = newRotation; };
	inline void SetScale(glm::vec3 newScale) { scale = newScale; };

	//Pure virtual method of Component overriden
	inline void f() override { printf("virtual function overriden"); };
private:
	//Attribute
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

