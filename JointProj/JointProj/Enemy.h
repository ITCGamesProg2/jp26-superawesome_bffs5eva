#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
public:
	void init();					//called to spawns enenmy
	void update();					//updates the enemy
									
private:
	void moveToPlayer(sf::Vector2f t_pos);	//moves towards player position
	void die();								//despawns/dissactivates enemy

	sf::Vector2f m_position{ 0.0f, 0.0f };;
	sf::Vector2f m_velocity;
	const static int m_MAX_SPEED{ 50 };

	const static int m_damadgeAmount{ 10 };

	bool m_isActive;
};