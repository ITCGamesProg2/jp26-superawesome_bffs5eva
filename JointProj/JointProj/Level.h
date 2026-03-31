#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Door.h"
#include "Collectible.h"

class Level
{
public:
	void loadLevel();				//sets up level
	void checkCollision();			//checks collisions to world

	int getTile(int t_x, int t_y) const;

	static const int MAP_WIDTH = 10;
	static const int MAP_HEIGHT = 10;
									
private:
	int m_map[MAP_HEIGHT][MAP_WIDTH];

	std::vector<sf::Sprite> m_walls;
	std::vector<Door> m_doors;
	std::vector<Collectible> m_collectibles;
};