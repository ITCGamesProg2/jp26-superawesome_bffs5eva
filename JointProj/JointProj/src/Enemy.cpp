#include "../include/Enemy.h"

void Enemy::init(int t_levelWidth, sf::Vector2f t_pos)
{
	m_isActive = true;
	m_levelWidth = t_levelWidth;
	m_position = t_pos;
	m_velocity = { 0.0f, 0.0f };
}

void Enemy::update(std::vector<int> t_path)
{
	std::cout << t_path.size() << std::endl;

	if (!t_path.empty() && (m_path.size() < 2 || m_path.back() != t_path.back()))
	{
		m_path = t_path;
	}

	moveTowardsPlayer();
}

void Enemy::moveTowardsPlayer()
{
	if (m_path.size() < 2) return;

	int nextCell = m_path[1];

	int row = nextCell / m_levelWidth;
	int col = nextCell % m_levelWidth;

	m_targetPos = { (float)col + 0.5f, (float)row + 0.5f };
	m_direction = m_targetPos - m_position;

	float length = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);

	if (length < 0.1f)
	{
		m_position = m_targetPos;
		m_path.erase(m_path.begin());

		return;
	}

	if (length > 0.0f)
	{
		m_direction /= length;
	}

	m_velocity = m_direction * 0.05f;
	m_position += m_velocity;
}

void Enemy::die()
{
	m_isActive = false;
}

sf::Vector2f Enemy::getPosition() const
{
	return m_position;
}