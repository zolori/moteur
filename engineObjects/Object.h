#pragma once
#include <string>
#include <vector>
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
	Object(std::string Name);
	//Name Getter
	inline std::string GetName() { return name; }
	//Return the component(s) of the object
	inline std::vector<Component*> GetComponents()  { return components; }
	//Access specific component
	Component* GetSpecificComponent(ComponentName componentName);

	/**
	* Add a component to the object
	* @param ComponentToAdd A pointer pointing toward the component you wish to add to the object
	*/
	inline void AddComponent(Component* ComponentToAdd) { components.push_back(ComponentToAdd); }
	//Remove a component from the object
	void RemoveComponent(ComponentName ComponentName);

	virtual void Update() {};
private:
	std::string name;
	std::vector<Component*> components;
};

