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
	//Moving the body
	Vector2D currentPosition(this->sprite->getPosition().x, this->sprite->getPosition().y);
	this->sprite->setPosition(currentPosition.x + this->velocity.x, currentPosition.y + this->velocity.y);
	//Normalizing the direction vector
	direction.Normalize();
	//Apply Acceleration
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

	//Limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;
}

bool Rigidbody::TestCollision(sf::Sprite spriteA, sf::Sprite spriteB)
{
	sf::FloatRect rectA = spriteA.getGlobalBounds();
	sf::FloatRect rectB = spriteB.getGlobalBounds();

	if (
		rectA.left + rectA.width >= rectB.left &&
		rectB.left + rectB.width >= rectA.left &&

		rectA.top + rectA.height >= rectB.top &&
		rectB.top + rectB.height >= rectA.top )
	{
		return true;
	}
	return false;
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
