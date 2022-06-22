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
	this->sprite.scale(1.f, 1.2f);
}

void Enemy::initVariables()
{
}

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::Update()
{

}

void Enemy::Render(sf::RenderTarget& target)
{
	
}
