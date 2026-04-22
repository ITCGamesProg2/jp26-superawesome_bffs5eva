#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet();
	void init(sf::Vector2f t_playerPos, float t_playerAngle);					//called to fire bullet
	void update();					//updates position
	void checkCollision();			//with walls and enemy
	bool checkActive() const;
	sf::Vector2f getPosition() const;
									
private:
	sf::Vector2f position{ -10.0f, -10.0f };
	float m_rotation = 0;
	const static int SPEED{ 100 };

	int lifeTime = 0;

	bool isActive;
};