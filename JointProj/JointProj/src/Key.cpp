#include "../include/Key.h"

void Key::init(sf::Vector2f t_pos)
{
	m_position = t_pos;
}

void Key::pickup()
{
	m_isACtive = false;
}