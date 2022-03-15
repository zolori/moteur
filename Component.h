//Miscellaneous
#include <string>
#include <unordered_map>
#pragma once
class Component
{
public:
	//Constructeur
	Component(std::string Name);
	//Getter
	inline std::string GetName() { return name; };
	//Pure virtual function to override to create a non abstract daughter of this class
	virtual void f() = 0;
private:
	//Attribute
	std::string name;
	std::unordered_map(std::string, )
};

