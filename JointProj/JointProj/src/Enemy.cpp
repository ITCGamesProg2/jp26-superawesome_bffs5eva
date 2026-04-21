#include "../include/Enemy.h"

Enemy::Enemy()
{
	if (!m_texture.loadFromFile("Resources\\ASSETS\\IMAGES\\enemy_spritesheet.png"))
	{
		std::cout << "problem loading enemy texture" << std::endl;
	}
	
	m_state = States::Idle;
	m_sprite.setTexture(m_texture,true);
	m_sprite.setTextureRect(sf::IntRect({ 0,0 }, { 48, 48 }));
	m_sprite.setOrigin({ 24.0f, 24.0f });
}

void Enemy::init(int t_levelWidth, sf::Vector2f t_pos)
{
	m_levelWidth = t_levelWidth;
	m_isActive = true;
	m_state = States::Idle;
	m_position = t_pos;
	m_velocity = { 0.0f, 0.0f };
}

void Enemy::update(float t_dt, const Level& t_level, bool t_sameCell, std::vector<int> t_path, sf::Vector2f t_playerPos)
{
	/*switch (m_state)
	{
	case States::Idle:
	{
		if ()
		{
			m_state = States::Run;
		}
		else if (t_sameCell)
		{
			m_state = States::Attack;
		}
		else if ()
		{
			m_state = States::Die;
		}

		break;
	}
	case States::Run:
	{*/
		if (!t_path.empty() && (m_path.size() < 2 || m_path.back() != t_path.back()))
		{
			m_path = t_path;
		}

		railMoveTowards();

		if (t_sameCell)
		{
	//		m_state = States::Attack;
	//	}

	//	break;
	//}
	//case States::Attack:
	//{
		independantMoveTowards(t_dt, t_level, t_playerPos);

	//	if(!t_sameCell)
	//	{
	//		m_state = States::Run;
	//	}
	//	else if ()
	//	{
	//		m_state = States::Die;
	//	}

	//	break;
	//}
	//case States::Die:
	//{
	//	m_isActive = false;

	//	break;
	//}
	}
}

void Enemy::railMoveTowards()
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

void Enemy::independantMoveTowards(float t_dt, const Level& t_level, sf::Vector2f t_playerPos)
{
	float dtSeconds = t_dt / 1000.0f;

	m_direction = t_playerPos - m_position;
	float length = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);

	if (length != 0)
	{
		m_direction /= length;
	}

	m_velocity = m_direction * 0.05f;

	sf::Vector2f newPosX = m_position;
	newPosX.x += m_velocity.x * dtSeconds;

	if (t_level.getTileType((int)newPosX.x, (int)newPosX.y) == 0) m_position.x = newPosX.x;
	else m_velocity.x = 0.0f;

	sf::Vector2f newPosY = m_position;
	newPosY.y += m_velocity.y * dtSeconds;

	if (t_level.getTileType((int)newPosY.x, (int)newPosY.y) == 0) m_position.y = newPosY.y;
	else m_velocity.y = 0.0f;
}

void Enemy::die()
{
	m_isActive = false;
}

sf::Vector2f Enemy::getPosition() const
{
	return m_position;
}

sf::Sprite Enemy::getSprite() const
{
	return m_sprite;
}