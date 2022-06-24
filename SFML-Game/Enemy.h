#pragma once
#include "SFLibrary.h"
#include "Vector2D.h"
#include "Rigidbody.h"
#include <iostream>

class Enemy
{
private:

	sf::Sprite sprite;
	sf::Texture texture;

	Vector2D direction, position;
	float size = 1.f;
	
	//Physics
	Rigidbody rigidBody;
	float velocityMax = 3.5f;
	float velocityMin = .0f;
	float acceleration = 1.f;
	float mass = .004f;

	//Private functions
	void initTexture();
	void initSprite();
	void initPhysics();

public:
	Enemy();
	Enemy(Vector2D position, float size, float acceleration);
	virtual ~Enemy();

	bool TestCollision(sf::Sprite spriteA, sf::Sprite spriteB);

	void SetPosition(float x, float y);
	void SetDirection(Vector2D direction);

	const Vector2D getPosition() const;
	const sf::Sprite getSprite() const;

	void Update(const sf::RenderTarget* target);
	void Render(sf::RenderTarget& target);
};

