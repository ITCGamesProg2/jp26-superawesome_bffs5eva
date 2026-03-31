#pragma once

#include <SFML/Graphics.hpp>

#include "Level.h"

#include "BulletManager.h"

class Player
{
public:
	void update();					//updates the player
	void handleInput(float t_dt, const Level& t_level);

	void takeDamadge(int t_amount);	//lowers health
	void pickup();					//pick up item

	sf::Vector2f getPosition() const;
	float getAngle() const;
									
private:
	void shoot();					//shoots a bullet
	void useCollectible();			//uses a collectible - caculates heal amount
	void heal(int t_amount);		//highens health

	sf::Vector2f m_position{ 5.0f, 5.0f };
	sf::Vector2f m_forward{ 0.0f, 0.0f };
	sf::Vector2f m_strafe{ 0.0f, 0.0f };

	sf::Vector2f m_velocity{ 0.0f, 0.0f };
	float m_acceleration{ 30.0f };
	float m_friction{ 0.85f };
	const float m_MAX_SPEED{ 10.0f };

	float m_angle{ 0.0f };
	const static int m_ROTATION_SPEED{ 2 };

	const static int MAX_HEALTH{ 100 };
	int health{ MAX_HEALTH };

	BulletManager bulletManager;

	int collectibleCount{ 0 };
	int keyCount{ 0 };
};