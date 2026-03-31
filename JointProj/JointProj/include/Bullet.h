#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	void init();					//called to fire bullet
	void update();					//updates position
	void checkCollision();			//with walls and enemy
									
private:
	sf::Vector2f position{ 0.0f, 0.0f };
	sf::Angle m_rotation{ sf::degrees(0.0) };
	const static int SPEED{ 100 };

	bool isActive;
};