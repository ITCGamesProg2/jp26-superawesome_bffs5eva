#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
public:
	void init();					//called to spawns enenmy
	void update();					//updates the enemy
									
private:
	void moveTowardsPlayer();		//moves towards player position
	void die();						//despawns/dissactivates enemy

	sf::Vector2f position{ 0.0f, 0.0f };;
	sf::Vector2f m_velocity;
	const static int MAX_SPEED{ 50 };

	const static int damadgeAmount{ 10 };

	bool isActive;
};