#pragma once

#include "Item.h"

class Key : Item
{
	void init();
	void pickup() override;
};