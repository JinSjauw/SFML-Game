#include "Rigidbody.h"

Rigidbody::Rigidbody()
{
	this->sprite = nullptr;
}

Rigidbody::Rigidbody(sf::Sprite &sprite)
{
	this->sprite = &sprite;
}

Rigidbody::Rigidbody(sf::Sprite &sprite, float velocityMax, float velocityMin, float acceleration, float mass)
{
	this->sprite = &sprite;
	this->velocityMax = velocityMax;
	this->velocityMin = velocityMin;
	this->acceleration = acceleration;
	this->mass = mass;
	this->drag = drag - mass;
}

Rigidbody::~Rigidbody()
{
	
}

void Rigidbody::setVelocityLimits(float max, float min)
{
	this->velocityMax = max;
	this->velocityMin = min;
}

void Rigidbody::setAcceleration(float acceleration)
{
	this->acceleration = acceleration;
}

void Rigidbody::setDrag(float drag)
{
	this->drag = drag;
}

void Rigidbody::setMass(float mass)
{
	this->mass = mass;
}

void Rigidbody::AddForce(Vector2D direction)
{
	Vector2D currentPosition(this->sprite->getPosition().x, this->sprite->getPosition().y);
	this->sprite->setPosition(currentPosition.x + this->velocity.x, currentPosition.y + this->velocity.y);
	//Normalizing the direction vector
	direction.Normalize();
	//Acceleration
	this->velocity += direction * this->acceleration;

	//Limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
	if (std::abs(this->velocity.y) > this->velocityMax)
	{
		this->velocity.y = this->velocityMax * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}
}

void Rigidbody::UpdatePhysics()
{
	//Deceleration
	this->velocity *= this->drag;

	//std::cout << "Velocity: " << this->velocity << std::endl;

	//Limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;
}

void Rigidbody::TestCollision()
{
	//Discrete Collision detection 
	//Check if 2 objects intersects

	//Use Sweep and Prune to check what objects need to be tested for collision;
	//Sorted list will be filled with Rigidbodies

	//The Sweep and Prune runs in the Game.cpp. 
	//The collision test gets called on the objects that are in the active interval list
}

void Rigidbody::UpdateWindowBoundCollision(const sf::RenderTarget* target)
{
	//Left
	if (this->sprite->getGlobalBounds().left <= 0.f)
	{
		this->sprite->setPosition(0.f, this->sprite->getGlobalBounds().top);
	}
	//Right
	if (this->sprite->getGlobalBounds().left + this->sprite->getGlobalBounds().width >= target->getSize().x)
	{
		this->sprite->setPosition(target->getSize().x - this->sprite->getGlobalBounds().width, this->sprite->getGlobalBounds().top);
	}
	//Bottom
	if (this->sprite->getGlobalBounds().top + this->sprite->getGlobalBounds().height >= target->getSize().y)
	{
		this->sprite->setPosition(this->sprite->getGlobalBounds().left, target->getSize().y - this->sprite->getGlobalBounds().height);
	}
}
