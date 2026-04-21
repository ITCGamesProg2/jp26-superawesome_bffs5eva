#include "../include/Bullet.h"

Bullet::Bullet()
{
	body.setSize(sf::Vector2f(5, 5));
	body.setPosition(position);
	body.setFillColor(sf::Color::Green);
	isActive = false;
}

void Bullet::init(sf::Vector2f t_playerPos, float t_playerAngle)
{
	isActive = true;
	m_rotation = t_playerAngle;
	body.setPosition(t_playerPos);
}

void Bullet::update()
{
	if (isActive)
	{
		position.x += (SPEED + m_rotation);
		position.y += (SPEED + m_rotation);
		body.setPosition(position);
	}
}

bool Bullet::checkActive() const
{
	return isActive;
}

sf::RectangleShape Bullet::getBody() const
{
	return body;
}
