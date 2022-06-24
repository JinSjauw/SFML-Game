#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2D.h"
class Rigidbody
{
private:
	//Physics

	//Velocity
	Vector2D velocity;
	sf::Sprite* sprite;
	float velocityMax = 4.f;
	float velocityMin = .1f;
	float acceleration = .2f;
	float drag = 1.f;
	float mass = 0.f;

public:
	Rigidbody();
	Rigidbody(sf::Sprite& sprite);
	Rigidbody(sf::Sprite& sprite, float velocityMax, float velocityMin, float acceleration, float mass);
	virtual ~Rigidbody();

	void setVelocityLimits(float max, float min);
	void setAcceleration(float acceleration);
	void setDrag(float drag);
	void setMass(float mass);

	void AddForce(Vector2D direction);
	void UpdatePhysics();
	bool TestCollision(sf::Sprite spriteA, sf::Sprite spriteB);
	void UpdateWindowBoundCollision(const sf::RenderTarget* target);
};

