#pragma once
#include "SFLibrary.h"
#include "Vector2D.h"
#include "Rigidbody.h"

class Player
{
private:

	sf::Sprite sprite;
	sf::Texture texture;

	Rigidbody rigidBody;

	//Physics
	float velocityMax;
	float velocityMin;
	float acceleration;
	float mass;

	//Private functions
	void initTexture();
	void initSprite();
	void initPhysics();

public:

	Player();
	virtual ~Player();

	//Functions
	const sf::Sprite getSprite() const;
	void setPositicon(float x, float y);
	void UpdatePlayerInput();

	void Update(const sf::RenderTarget* target);
	void Render(sf::RenderTarget& target);
};

