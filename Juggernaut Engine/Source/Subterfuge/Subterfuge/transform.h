#pragma once

#include <SFML/System.hpp>

class transform
{
public:
	transform();
	~transform();

	sf::Vector2f Position;
	float Rotation;
	float Scale;
};

