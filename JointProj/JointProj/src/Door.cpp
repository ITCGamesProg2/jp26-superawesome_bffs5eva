#include "../include/Door.h"

void Door::open()
{
	doorOpen = !doorOpen;
}

bool Door::draw() const
{
	return doorOpen;
}
