//Miscellaneous
#include "ComponentName.h"
#pragma once
class Component
{
public:
	//Constructor
	Component();
	//Copy Constructeur
	Component(Component&) = delete;
	//Move constructeur
	Component(Component&&) = default;
	//Pure virtual function to override to create a non abstract daughter of this class
	virtual void f() = 0;
	//Attribute
	ComponentName name;

};

