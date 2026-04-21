#pragma once

#include <SFML/Graphics.hpp>

#include "Level.h"

enum States {Idle, Run, Attack, Die};

class Enemy
{
public:
	Enemy();
	void init(int t_levelWidth, sf::Vector2f t_pos);					//called to spawns enenmy

	void update(float t_dt, const Level& t_level, bool t_sameCell, std::vector<int> t_path, sf::Vector2f t_playerPos);					//updates the enemy

	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
									
private:
	void railMoveTowards();		//moves towards player position
	void independantMoveTowards(float t_dt, const Level& t_level, sf::Vector2f t_playerPos);
	void die();						//despawns/dissactivates enemy

	int m_state;

	int m_levelWidth;

	std::vector<int> m_path;
	sf::Vector2f m_targetPos;
	sf::Vector2f m_direction;

	sf::Vector2f m_position{ 0.0f, 0.0f };
	sf::Vector2f m_velocity;
	const static int m_MAX_SPEED{ 50 };

	const static int m_damadgeAmount{ 10 };

	sf::Texture m_texture;
	sf::Sprite m_sprite{ m_texture };

	bool m_isActive;
};