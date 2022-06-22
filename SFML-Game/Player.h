#pragma once
#include "SFLibrary.h"
#include "Vector2D.h"

class Player
{
private:

	sf::Sprite sprite;
	sf::Texture texture;

	//Physics
	Vector2D velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;

	//Private functions
	void initTexture();
	void initSprite();
	void initVariables();
	void initPhysics();

public:

	Player();
	virtual ~Player();

	//Functions
	sf::Sprite getSprite();
	void setPositicon(float x,  float y);
	void Move(Vector2D direction);

	void UpdatePhysiscs();
	void UpdateWindowCollision(const sf::RenderTarget* target);
	void UpdatePlayerInput();

	void Update(const sf::RenderTarget* target);
	void Render(sf::RenderTarget& target);
};

