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
	inline std::vector<std::unique_ptr<Component>> GetComponents()  { return components; };
	//Function
	inline void AddComponent(std::unique_ptr<Component> ComponentToAdd) { components.push_back(std::move(ComponentToAdd)); };
	void RemoveComponent(std::string ComponentName);
private:
	std::string name;
	std::string tag;
	std::vector<std::unique_ptr<Component>> components;
};

