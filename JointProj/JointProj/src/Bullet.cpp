#include "../include/Bullet.h"

Bullet::Bullet()
{
	body.setSize(sf::Vector2f(5, 5));
	body.setPosition(position);
	body.setFillColor(sf::Color::Green);
	isActive = false;
}

void Bullet::init(sf::Vector2f t_playerPos, sf::Vector2f t_playerAngle)
{
	isActive = true;
	body.setPosition(t_playerPos);
}

void Bullet::update()
{
	if (isActive)
	{
		position.x += (SPEED + t_playerAngle.x);
		position.y += (SPEED + t_playerAngle.y);
		body.setPosition(position);
	}
}

bool Bullet::checkActive() const
{
	return isActive;
}
