#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Component.h"

enum ComponentType { };

class Object
{
public:
	//Constructeur
	Object(std::string Name, std::string Tag);
	//Getter
	inline std::string GetName() { return name; };
	inline std::string GetTag() { return tag; };
	inline std::vector<std::unique_ptr<Component>> GetComponents()  { return std::move(components); };
	//Function
	inline void AddComponent(std::unique_ptr<Component> ComponentToAdd) { components.push_back(std::move(ComponentToAdd)); };
	void RemoveComponent(ComponentName ComponentName);

	virtual void Update() {};
	virtual void Draw() {};
private:
	std::string name;
	std::string tag;
	std::vector<std::unique_ptr<Component>> components;
};

