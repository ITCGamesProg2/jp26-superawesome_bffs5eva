#pragma once

#include <SFML/Graphics.hpp>

class Door
{
public:
	void open();					//become opened
									
	bool m_isOpen{ false };

private:
	sf::Vector2f m_position{ 0.0f, 0.0f };
};