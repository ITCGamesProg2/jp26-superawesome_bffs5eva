#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	void init(sf::Vector2f t_pos, sf::Angle t_rot);		//called to fire bullet
	void update();										//updates position
	void checkCollision();								//with walls and enemy
									
private:
	sf::Vector2f m_position{ 0.0f, 0.0f };
	sf::Angle m_rotation{ sf::degrees(0.0) };
	const static int m_SPEED{ 100 };

	bool m_isActive;
};