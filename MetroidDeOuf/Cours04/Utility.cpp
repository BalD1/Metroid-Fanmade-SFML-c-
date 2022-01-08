#include "stdafx.hpp"
#include "Utility.hpp"

#pragma region Vectors

sf::Vector2f Vector2zero()
{
	sf::Vector2f v = sf::Vector2f(0, 0);
	return v;
}

sf::Vector2f AddVectors(sf::Vector2f a, sf::Vector2f b)
{
	a.x += b.x;
	a.y += b.y;

	return a;
}

sf::Vector2f AddVectors(sf::Vector2f a, float b)
{
	a.x += b;
	a.y += b;

	return a;
}

sf::Vector2f SubVectors(sf::Vector2f a, sf::Vector2f b)
{
	a.x -= b.x;
	a.y -= b.y;

	return a;
}

sf::Vector2f SubVectors(sf::Vector2f a, float b)
{
	a.x -= b;
	a.y -= b;

	return a;
}

sf::Vector2f MultVectors(sf::Vector2f a, sf::Vector2f b)
{
	a.x *= b.x;
	a.y *= b.y;

	return a;
}

sf::Vector2f MultVectors(sf::Vector2f a, float b)
{
	a.x *= b;
	a.y *= b;

	return a;
}

sf::Vector2f DivVectors(sf::Vector2f a, sf::Vector2f b)
{
	a.x /= b.x;
	a.y /= b.y;

	return a;
}

sf::Vector2f DivVectors(sf::Vector2f a, float b)
{
	a.x /= b;
	a.y /= b;

	return a;
}

float Dot(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.x + a.y * b.y;
}

float Norm(sf::Vector2f vector)
{
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

sf::Vector2f NormalizeVector(sf::Vector2f vector)
{
	vector = DivVectors(vector, Norm(vector));
	return vector;
}

sf::Vector2f Project(sf::Vector2f a, const sf::Vector2f b)
{
	a = MultVectors(NormalizeVector(a), Dot(b, a) / Norm(a));

	return a;
}

sf::Vector2f Reflect(sf::Vector2f a, sf::Vector2f b)
{
	a = AddVectors(a, MultVectors(Project(a, b), -2));
	return a;
}

sf::Vector2f vectoriToVectorf(sf::Vector2i v)
{
	return sf::Vector2f(v.x, v.y);
}

sf::Vector2i vectorfToVectori(sf::Vector2f v)
{
	return sf::Vector2i(v.x, v.y);
}

#pragma endregion

float catmul(float p0, float p1, float p2, float p3, float t)
{
	float q = p1 * 2.0f;
	float t2 = t * t;

	q += (-p0 + p2) * t;
	q += (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2;
	q += (-p0 + 3.0f * p1 - 3 * p2 + p3) * t2 * t;

	return 0.5 * q;
}

float clamp(float v, const float min, const float max)
{
	if (v > max)
		v = max;
	if (v < min)
		v = min;
	return v;
}
