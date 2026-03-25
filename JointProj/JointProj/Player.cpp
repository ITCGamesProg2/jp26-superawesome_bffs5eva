#include "Player.h"
#include "Enemy.h"

void Player::update()
{
}

void Player::move()
{
}

void Player::rotate()
{
}

void Player::shoot()
{
}

void Player::pickup()
{
}

void Player::takeDamadge(int t_amount)
{
	m_health = m_health - t_amount;
}

void Player::useCollectible()
{
	if (m_collectibleCount > 0 && m_health < m_MAX_HEALTH)
	{
		int healAmount = m_cardHand.calculateValue();
		heal(healAmount);
	}
}

void Player::heal(int t_amount)
{
	m_health = m_health + t_amount;
}