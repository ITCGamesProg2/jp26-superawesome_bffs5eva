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
	lifeTime = 100;
}

void Bullet::update()
{
	if (isActive)
	{
		position.x += m_rotation;
		position.y += m_rotation;
		lifeTime--;
		remove();
	}
}

void Bullet::remove()
{
	if (lifeTime <= 0)
	{
		isActive = false;
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
