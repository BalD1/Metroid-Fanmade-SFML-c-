#pragma once

#pragma region Vectors

sf::Vector2f Vector2zero();

sf::Vector2f AddVectors(sf::Vector2f a, sf::Vector2f b);
sf::Vector2f AddVectors(sf::Vector2f a, float b);

sf::Vector2f SubVectors(sf::Vector2f a, sf::Vector2f b);
sf::Vector2f SubVectors(sf::Vector2f a, float b);

sf::Vector2f MultVectors(sf::Vector2f a, sf::Vector2f b);
sf::Vector2f MultVectors(sf::Vector2f a, float b);

sf::Vector2f DivVectors(sf::Vector2f a, sf::Vector2f b);
sf::Vector2f DivVectors(sf::Vector2f a, float b);

float Dot(sf::Vector2f a, sf::Vector2f b);
float Norm(sf::Vector2f vector);
sf::Vector2f NormalizeVector(sf::Vector2f vector);

sf::Vector2f Project(sf::Vector2f a, const sf::Vector2f b);
sf::Vector2f Reflect(sf::Vector2f a, sf::Vector2f b);

sf::Vector2f vectoriToVectorf(sf::Vector2i v);
sf::Vector2i vectorfToVectori(sf::Vector2f v);

#pragma endregion

float catmul(float p0, float p1, float p2, float p3, float t);

float clamp(float v, const float min, const float max);