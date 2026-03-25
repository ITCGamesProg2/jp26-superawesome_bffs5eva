#pragma once

#include <SFML/Graphics.hpp>

#include "BulletManager.h"

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

	sf::Vector2f position{ 0.0f, 0.0f };
	sf::Angle m_rotation{ sf::degrees(0.0) };
	sf::Vector2f m_velocity;
	const static int MAX_SPEED{ 50 };

	const static int MAX_HEALTH{ 100 };
	int health{ MAX_HEALTH };

	BulletManager bulletManager;

	int collectibleCount{ 0 };
	int keyCount{ 0 };
};