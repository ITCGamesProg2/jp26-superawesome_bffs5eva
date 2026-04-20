#include "../include/Bullet.h"

void Bullet::init(sf::Vector2f t_pos, sf::Angle t_rot)
{
	m_isActive = true;
	m_position = t_pos;
	m_rotation = t_rot;
}

void Bullet::update(float t_dt)
{
	//update position

	checkCollision();
}

void Bullet::checkCollision()
{
	bool collided = false;

	if (collided)
	{
		m_isActive = false;
	}
}