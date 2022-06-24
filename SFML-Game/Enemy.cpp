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

bool Enemy::TestCollision(sf::Sprite spriteA, sf::Sprite spriteB)
{
	return this->rigidBody.TestCollision(spriteA, spriteB);
}

void Enemy::SetPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Enemy::SetDirection(Vector2D direction)
{
	direction.Normalize();
	this->direction = direction;
}

const Vector2D Enemy::getPosition() const
{
	Vector2D position;
	position.x = this->sprite.getPosition().x;
	position.y = this->sprite.getPosition().y;
	return position;
}

const sf::Sprite Enemy::getSprite() const
{
	return this->sprite;
}

void Enemy::Update(const sf::RenderTarget* target)
{	
	this->rigidBody.UpdatePhysics();
	this->rigidBody.AddForce(this->direction);
}

void Enemy::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
