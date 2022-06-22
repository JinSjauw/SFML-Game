#include <iostream>
#include "Player.h"

void Player::initTexture()
{
	//Load texture from file
	if (!this->texture.loadFromFile("Assets/rocket.png")) 
	{
		std::cout << "Texture NOT FOUND in Player.cpp" << std::endl;
	}
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	//Resize sprite
	this->sprite.scale(1.f, 1.2f);
}

void Player::initVariables()
{
}

void Player::initPhysics()
{
	this->velocityMax = 3.5f;
	this->velocityMin = .001f;
	this->acceleration = .4f;
	this->drag = 0.996f;
}

Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->initPhysics();
}

Player::~Player()
{
}

sf::Sprite Player::getSprite()
{
	return this->sprite;
}

void Player::setPositicon(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Player::Move(Vector2D direction)
{
	Vector2D currentPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);
	this->sprite.setPosition(currentPosition.x + this->velocity.x, currentPosition.y + this->velocity.y);
	//Acceleration
	//this->velocity *= this->acceleration;
	//std::cout << "Not Normalized: " << direction << std::endl;
	direction.Normalize();
	//std::cout << "Normalized: " << direction << std::endl;
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

void Player::UpdatePhysiscs()
{
	//Deceleration
	this->velocity *= this->drag;

	//Limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	//std::cout << "Velocity: " << this->velocity << std::endl;
}

void Player::UpdateWindowCollision(const sf::RenderTarget* target)
{
	//Left
	if (this->sprite.getGlobalBounds().left <= 0.f) 
	{
		this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
	}
	//Right
	if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x) 
	{
		this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
	}
	//Bottom
	if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target->getSize().y) 
	{
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, target->getSize().y - this->sprite.getGlobalBounds().height);
	}
}

void Player::UpdatePlayerInput()
{
	Vector2D movementDirection;

	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movementDirection.x = -1.f;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
	{
		movementDirection.x = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movementDirection.x = 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movementDirection.y = -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movementDirection.y = 1.f;
	}
	Move(movementDirection);
}

void Player::Update(const sf::RenderTarget* target)
{
	UpdateWindowCollision(target);
	UpdatePhysiscs();
	UpdatePlayerInput();
}

void Player::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
