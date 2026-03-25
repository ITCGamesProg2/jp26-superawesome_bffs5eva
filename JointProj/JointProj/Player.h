#pragma once

#include <SFML/Graphics.hpp>

#include "BulletManager.h"
#include "Cards.h"

class Player
{
public:
	void update();					//updates the player
	void takeDamadge(int t_amount);	//lowers health
	void pickup();					//pick up item
									
private:
	void move();					//moves player
	void rotate();					//rotates player view
	void shoot();					//shoots a bullet
	void useCollectible();			//uses a collectible - caculates heal amount
	void heal(int t_amount);		//highens health

	sf::Vector2f m_position{ 0.0f, 0.0f };
	sf::Angle m_rotation{ sf::degrees(0.0) };
	sf::Vector2f m_velocity;
	const static int m_MAX_SPEED{ 50 };

	const static int m_MAX_HEALTH{ 100 };
	int m_health{ m_MAX_HEALTH };

	BulletManager m_bulletManager;

	Cards m_cardHand;

	int m_collectibleCount{ 0 };
	int m_keyCount{ 0 };
};