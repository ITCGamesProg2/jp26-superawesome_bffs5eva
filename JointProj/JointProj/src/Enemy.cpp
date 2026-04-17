#include "../include/Enemy.h"

void Enemy::init()
{
	m_isActive = true;
	m_position = { 0.0f, 0.0f };
	m_velocity = { 0.0f, 0.0f };
}

void Enemy::update(std::vector<int> t_path)
{
	if (!t_path.empty())
	{
		m_path = t_path;
	}


}

void Enemy::moveTowardsPlayer()
{
	//std::vector<int> path = Level::breadthFirstSearch(1, 1);
}

void Enemy::die()
{
	m_isActive = false;
}

sf::Vector2f Enemy::getPosition() const
{
	return m_position;
}
