#pragma once

#include <SFML/Graphics.hpp>

#include "Level.h"

class Enemy
{
public:
	void init(int t_levelWidth, sf::Vector2f t_pos);					//called to spawns enenmy
	void update(std::vector<int> t_path);					//updates the enemy

	sf::Vector2f getPosition() const;
									
private:
	void moveTowardsPlayer();		//moves towards player position
	void die();						//despawns/dissactivates enemy

	int m_levelWidth;

	std::vector<int> m_path;
	sf::Vector2f m_targetPos;
	sf::Vector2f m_direction;

	sf::Vector2f m_position{ 0.0f, 0.0f };
	sf::Vector2f m_velocity;
	const static int m_MAX_SPEED{ 50 };

	const static int m_damadgeAmount{ 10 };

	bool m_isActive;
};