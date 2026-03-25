#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Door.h"
#include "Collectible.h"

class Level
{
public:
	Level();
	void loadLevel();				//sets up level
	void draw(sf::RenderWindow &t_window);
	void checkCollision();			//checks collisions to world
									
private:

	//level length
	static int const MAX_ROW = 5;
	//level width
	static int const MAX_COL = 5;

	//tile size
	int const width = 100;
	int const height = 100;

	int m_levelData[MAX_ROW][MAX_COL] =
	{
		//0 = empty, 1 = wall
		{1,1,1,1,1},
		{1,0,0,0,1},
		{1,0,1,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1}
	};
	sf::RectangleShape m_level[MAX_ROW][MAX_COL];

	std::vector<sf::Sprite> m_walls;
	std::vector<Door> m_doors;
	std::vector<Collectible> m_collectibles;
};