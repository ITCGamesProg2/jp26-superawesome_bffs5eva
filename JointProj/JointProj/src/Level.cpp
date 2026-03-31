#include "../include/Level.h"

void operator >> (const YAML::Node& t_tileNode, tileData& t_tile)
{
	t_tile.m_type = t_tileNode["type"].as<int>();
}

void operator >> (const YAML::Node& t_levelNode, LevelData& t_level)
{
	t_level.m_width = t_levelNode["width"].as<int>();
	t_level.m_height = t_levelNode["height"].as<int>();

	const YAML::Node& mapNode = t_levelNode["map"].as<YAML::Node>();
	for (unsigned i = 0; i < mapNode.size(); ++i)
	{
		tileData tile;
		mapNode[i] >> tile;
		t_level.m_tiles.push_back(tile);
	}

	if (t_level.m_tiles.size() != t_level.m_width * t_level.m_height)
	{
		throw std::runtime_error("Map size does not match width * height");
	}
}

void Level::loadLevel(int t_levelNr, LevelData& t_level)
{
	std::string filename = "./resources/levelData/level" + std::to_string(t_levelNr) + ".yaml";
	YAML::Node baseNode = YAML::LoadFile(filename);
	baseNode >> m_level;
}

int Level::getTileType(int t_x, int t_y) const
{
	if (t_x < 0 || t_x >= m_level.m_width || t_y < 0 || t_y >= m_level.m_height) return 1;
	return m_level.m_tiles[t_y * m_level.m_width + t_x].m_type;
}