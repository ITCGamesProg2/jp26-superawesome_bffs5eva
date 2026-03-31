#include "Player.h"

void Player::handleInput(float t_dt, const Level& t_level)
{
	float dtSeconds = t_dt / 1000.0f;

	sf::Vector2f newPos = m_position;

	m_movement = { cos(m_angle), sin(m_angle) };
	m_straffe = { cos(m_angle + 3.14159f / 2), sin(m_angle + 3.14159f / 2) };

	float moveStep = m_moveSpeed * dtSeconds;
	float rotStep = m_rotSpeed * dtSeconds;

	//forwrd and back movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		newPos = m_position + (m_movement * moveStep);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		newPos = m_position - (m_movement * moveStep);
	}

	//side straffing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		newPos = m_position - (m_straffe * moveStep);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		newPos = m_position + (m_straffe * moveStep);
	}

	//rotating
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		m_angle = m_angle - rotStep;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		m_angle = m_angle + rotStep;
	}

	if (t_level.getTile((int)newPos.x, (int)newPos.y) == 0)
	{
		m_position = newPos;
	}
}

sf::Vector2f Player::getPosition() const
{
	return m_position;
}

float Player::getAngle() const
{
	return m_angle;
}