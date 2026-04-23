#include "../include/Collectible.h"

void Collectible::init(sf::Vector2f t_pos)
{
    m_position = t_pos;
}

void Collectible::pickup()                  //become picked up
{
    if (!m_isActive) return;

    m_isActive = false;
    notify(EventType::COLLECTIBLE_ACQUIRED);
}

sf::Vector2f Collectible::getPosition() const
{
    return m_position;
}