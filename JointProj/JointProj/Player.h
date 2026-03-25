#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	void update();
	void takeDamadge();
	void pickup();

private:
	void move();
	void rotate();
	void shoot();
	void useCollectible();
	void heal();

	sf::Vector2f position{ 0.0f, 0.0f };
	sf::Angle m_rotation{ sf::degrees(0.0) };
	sf::Vector2f m_velocity;
	const static int MAX_SPEED{ 50 };

	const static int MAX_HEALTH{ 100 };
	int health{ MAX_HEALTH };

	int collectibleCount{ 0 };
	int keyCount{ 0 };
};