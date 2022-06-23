#include "Enemy.h"


void Enemy::initTexture()
{
	if (!this->texture.loadFromFile("Assets/Asteroid.png"))
	{
		std::cout << "Texture NOT FOUND in Player.cpp" << std::endl;
	}
}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->texture);
	//Resize sprite
	//this->sprite.scale(1.f, 1.2f);
}

void Enemy::initPhysics()
{
	this->rigidBody = Rigidbody(
		this->sprite, this->velocityMax, this->velocityMin,
		this->acceleration, this->mass);
}

Enemy::Enemy()
{
	initTexture();
	initSprite();
	initPhysics();
}

Enemy::Enemy(Vector2D position, float size, float acceleration)
{
	this->acceleration = acceleration;
	this->sprite.scale(size, size);
	this->sprite.setPosition(position.x, position.y);
	initTexture();
	initSprite();
	initPhysics();
}

Enemy::~Enemy()
{

}

void Enemy::SetPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Enemy::SetDirection(Vector2D direction)
{
	direction.Normalize();
	this->rigidBody.AddForce(direction);
}

void Enemy::Update(const sf::RenderTarget* target)
{
	this->rigidBody.UpdateWindowBoundCollision(target);
	this->rigidBody.UpdatePhysics();
}

void Enemy::Render(sf::RenderTarget& target)
{
	std::cout << "Drawing enemy at: " << this->sprite.getPosition().x << " " << this->sprite.getPosition().y << std::endl;
	target.draw(this->sprite);
}
