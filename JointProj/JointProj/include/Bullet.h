#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet();
	void init(sf::Vector2f t_playerPos, sf::Vector2f t_playerAngle);					//called to fire bullet
	void update();					//updates position
	void checkCollision();			//with walls and enemy
	bool checkActive() const;
									
private:
	sf::RectangleShape body;
	sf::Vector2f position{ -10.0f, -10.0f };
	sf::Angle m_rotation{ sf::degrees(0.0) };
	const static int SPEED{ 100 };

	bool isActive;
};