#pragma once

#include "Item.h"

class Key : public Item
{
public:
    void init(sf::Vector2f t_pos);          //called to spawn key
    void pickup() override;                 //become picked up

    sf::Vector2f getPosition() const override;
};