#include "../include/Key.h"

void Key::init(sf::Vector2f t_pos)
{
    m_position = t_pos;
}

void Key::pickup()
{
    if (!m_isActive) return;

    m_isActive = false;
    notify(EventType::KEY_ACQUIRED);
}

sf::Vector2f Key::getPosition() const
{
    return m_position;
}