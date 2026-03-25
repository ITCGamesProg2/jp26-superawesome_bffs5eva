#pragma once

#include "Item.h"

class Key : Item
{
	void init();					//called to spawn key
	void pickup() override;			//become picked up
};