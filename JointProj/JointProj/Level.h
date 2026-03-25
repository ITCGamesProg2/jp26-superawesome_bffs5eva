#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Door.h"
#include "Collectible.h"

class Level
{
public:
	void loadLevel();
	void checkCollision();

private:
	std::vector<sf::Sprite> m_walls;
	std::vector<Door> m_doors;
	std::vector<Collectible> m_collectibles;
};