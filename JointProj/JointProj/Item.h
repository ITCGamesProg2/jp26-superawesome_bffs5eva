#pragma once

#include <SFML/Graphics.hpp>

class Item
{
public:
	virtual void pickup() = 0;

protected:
	sf::Vector2f position{ 0.0f, 0.0f };

	bool isACtive;
};