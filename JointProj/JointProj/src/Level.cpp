#include "../include/Level.h"

void operator >> (const YAML::Node& t_tileNode, tileData& t_tile)
{
	t_tile.m_type = t_tileNode["type"].as<int>();
}

void operator >> (const YAML::Node& t_levelNode, LevelData& t_level)
{
	t_level.m_width = t_levelNode["width"].as<int>();
	t_level.m_height = t_levelNode["height"].as<int>();

	const YAML::Node& mapNode = t_levelNode["map"];
	for (int y = 0; y < t_level.m_height; ++y)
	{
		for (int x = 0; x < t_level.m_width; ++x)
		{
			tileData tile;
			tile.m_type = mapNode[y][x].as<int>();
			t_level.m_tiles.push_back(tile);
		}
	}

	if (mapNode.size() != t_level.m_height)
	{
		throw std::runtime_error("Incorrect number of rows in map");
	}

	if (mapNode[0].size() != t_level.m_width)
	{
		throw std::runtime_error("Incorrect row width in map");
	}
}

void Level::loadLevel(int t_levelNr)
{
	std::string filename = "./resources/levelData/level" + std::to_string(t_levelNr) + ".yaml";
	YAML::Node baseNode = YAML::LoadFile(filename);
	baseNode >> m_level;
}

void Level::checkCollision()
{
}

int Level::getTileType(int t_x, int t_y) const
{
	if (t_x < 0 || t_x >= m_level.m_width || t_y < 0 || t_y >= m_level.m_height) return 1;
	return m_level.m_tiles[t_y * m_level.m_width + t_x].m_type;
}

int Level::getWidth() const
{ 
	return m_level.m_width; 
}

int Level::getHeight() const
{ 
	return m_level.m_height; 
}

bool Level::open() const
{
	return m_door.draw();
}
