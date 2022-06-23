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

void Player::initPhysics()
{
	this->velocityMax = 3.5f;
	this->velocityMin = .001f;
	this->acceleration = .4f;
	this->mass = .004f;

	this->rigidBody = Rigidbody(
		this->sprite, this->velocityMax, this->velocityMin, 
		this->acceleration, this->mass);
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
	this->rigidBody.AddForce(movementDirection);
}

void Player::Update(const sf::RenderTarget* target)
{
	this->rigidBody.UpdateWindowBoundCollision(target);
	this->rigidBody.UpdatePhysics();
	UpdatePlayerInput();
}

void Player::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
