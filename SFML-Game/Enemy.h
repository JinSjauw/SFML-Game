#pragma once
#include "SFLibrary.h"
#include <iostream>
class Enemy
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	//Private functions
	void initTexture();
	void initSprite();
	void initVariables();

public:

	Enemy();
	virtual ~Enemy();

	void Update();
	void Render(sf::RenderTarget& target);
};

