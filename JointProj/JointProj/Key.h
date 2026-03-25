#pragma once

#include "Item.h"

class Key : Item
{
	void init(sf::Vector2f t_pos);	//called to spawn key
	void pickup() override;			//become picked up
};