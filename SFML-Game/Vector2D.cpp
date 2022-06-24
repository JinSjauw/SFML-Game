#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;

}

Vector2D& Vector2D::Add(const Vector2D& vector)
{
	this->x += vector.x;
	this->y += vector.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vector)
{
	this->x -= vector.x;
	this->y -= vector.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vector)
{
	this->x *= vector.x;
	this->y *= vector.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vector)
{
	this->x /= vector.x;
	this->y /= vector.y;

	return *this;
}

Vector2D& Vector2D::Divide(float magnitude)
{
	this->x /= magnitude;
	this->y /= magnitude;

	return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vector)
{
	return this->Add(vector);
}

Vector2D& Vector2D::operator-=(const Vector2D& vector)
{
	return this->Subtract(vector);
}

Vector2D& Vector2D::operator*=(const Vector2D& vector)
{
	return this->Multiply(vector);
}

Vector2D& Vector2D::operator*=(const float& f)
{
	this->x *= f;
	this->y *= f;

	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& vector)
{
	return this->Divide(vector);
}

Vector2D& Vector2D::operator*(const float& f)
{
	this->x *= f;
	this->y *= f;

	return *this;
}

Vector2D& Vector2D::operator*(const Vector2D& vector)
{
	this->x *= vector.x;
	this->y *= vector.y;

	return *this;
}

Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;

	return *this;
}

float Vector2D::Magnitude()
{
	return sqrt(this->x * this->x + this->y * this->y);
}

Vector2D& Vector2D::Normalize()
{
	float magnitude = this->Magnitude();

	if (magnitude > 0)
	{
		this->Divide(magnitude);
	}

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vector)
{
	stream << "(" << vector.x << ", " << vector.y << ")";
	return stream;
}