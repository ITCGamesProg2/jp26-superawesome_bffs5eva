#pragma once

#include <SFML/Graphics.hpp>

class Item
{
public:
	virtual void pickup() = 0;		//virual void - become picked up
									
protected:
	sf::Vector2f m_position{ 0.0f, 0.0f };

	bool m_isACtive;
};