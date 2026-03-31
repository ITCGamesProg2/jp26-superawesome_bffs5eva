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
	void move();					//moves player
	void rotate();					//rotates player view

	void shoot();					//shoots a bullet
	void useCollectible();			//uses a collectible - caculates heal amount
	void heal(int t_amount);		//highens health

	sf::Vector2f m_position{ 5.0f, 5.0f };
	float m_angle{ 0.0f };

	float m_moveSpeed{ 3.0f };
	float m_rotSpeed{ 2.0f };

	sf::Vector2f m_movement{ cos(m_angle), sin(m_angle) };
	sf::Vector2f m_straffe{ cos(m_angle + 3.14159f / 2), sin(m_angle + 3.14159f / 2) };

	sf::Vector2f m_velocity;
	const static int MAX_SPEED{ 50 };

	const static int MAX_HEALTH{ 100 };
	int health{ MAX_HEALTH };

	BulletManager bulletManager;

	int collectibleCount{ 0 };
	int keyCount{ 0 };
};