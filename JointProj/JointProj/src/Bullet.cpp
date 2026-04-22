#include "../include/Bullet.h"

Bullet::Bullet()
{
	isActive = false;
}

void Bullet::init(sf::Vector2f t_playerPos, float t_playerAngle)
{
	isActive = true;
	m_rotation = t_playerAngle;
	position = t_playerPos;
}

void Bullet::update()
{
	if (isActive)
	{
		position.x += (SPEED + m_rotation);
		position.y += (SPEED + m_rotation);
	}
}

bool Bullet::checkActive() const
{
	return isActive;
}

sf::Vector2f Bullet::getPosition() const
{
	return position;
}
