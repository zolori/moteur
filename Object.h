#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Component.h"
class Object
{
public:
	/**
	* Constructor of the Object class
	* 
	* @param Name Name of the object
	* @param Tag Tag of the object
	*/
	Object(std::string Name, std::string Tag);
	//Name Getter
	inline std::string GetName() { return name; }
	//Tag Getter
	inline std::string GetTag() { return tag; }
	//Return the component(s) of the object
	inline std::vector<std::unique_ptr<Component>> GetComponents()  { return std::move(components); }
	
	/**
	* Add a component to the object
	* @param ComponentToAdd A pointer pointing toward the component you wish to add to the object
	*/
	inline void AddComponent(std::unique_ptr<Component> ComponentToAdd) { components.push_back(std::move(ComponentToAdd)); }
	//Remove a component from the object
	void RemoveComponent(ComponentName ComponentName);

	virtual void Update() {};
	virtual void Draw() {};
private:
	std::string name;
	std::string tag;
	std::vector<std::unique_ptr<Component>> components;
};

