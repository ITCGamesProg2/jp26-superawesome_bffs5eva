#pragma once

#include "Item.h"

class Collectible : public Item
{
public:
    void init(sf::Vector2f t_pos);
    void pickup() override;                 //become picked up

    sf::Vector2f getPosition() const override;
};