#pragma once
#include <iostream>
#include "Vector2D.h"

class GameObject
{
private:

	std::string name = "NoName";
	float xpos, ypos = 0.f;
	float scale = 1.f;

public:
	GameObject();
	GameObject(std::string name, float xpos, float ypos, float scale);
	virtual ~GameObject();
};

