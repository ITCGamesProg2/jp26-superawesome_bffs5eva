#include "Level.h"

void Level::loadLevel()
{
	int temp[MAP_HEIGHT][MAP_WIDTH] =
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,1,0,1,1,0,1,0,1},
		{1,0,1,0,0,0,0,1,0,1},
		{1,0,0,0,1,0,0,0,0,1},
		{1,0,1,0,1,0,1,0,0,1},
		{1,0,1,0,0,0,1,0,0,1},
		{1,0,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

	memcpy(m_map, temp, sizeof(m_map));
}

int Level::getTile(int t_x, int t_y) const
{
	if (t_x < 0 || t_x >= MAP_WIDTH || t_y < 0 || t_y >= MAP_HEIGHT)
	{
		return 1;
	}

	return m_map[t_y][t_x];
}