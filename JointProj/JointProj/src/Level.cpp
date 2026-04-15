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

	for (int i = 0; i < m_level.m_tiles.size(); i++)
	{
		loadTileNeighboors(i, i / m_level.m_width, i % m_level.m_width);
	}
}

void Level::loadTileNeighboors(int t_index, int t_row, int t_col)
{
	int tile = (t_row * m_level.m_width) + t_col;
	int rowOffset[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	int colOffset[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

	int newRow = 0;
	int newCol = 0;
	int newTile = 0;

	for (int i = 0; i < MAX_NEIGHBOORS; i++)
	{
		newRow = t_row + rowOffset[i];
		newCol = t_col + colOffset[i];

		if (newRow >= 0 && newRow < m_level.m_height && newCol >= 0 && newCol < m_level.m_width) 
		{
			newTile = (newRow * m_level.m_width) + newCol;
			m_level.m_tiles.at(t_index).m_neighboors.push_back(newTile);
		}
	}
}

std::vector<int> Level::breadthFirstSearch(int t_startCell, int t_endCell)
{
	//if (t_endCell != 0) //not a valid cell - improve check later
	//{
	//	return std::vector<int>();
	//}

	////make queue
	//std::queue<std::pair<tileData, bool>> queue;

	////label t_startCell as explored
	////push t_startCell
	//tileData startCell;
	//queue.push(std::pair{ startCell, true });

	////while queue is not empty
	//while (!queue.empty())
	//{
	//	//for each queue front
	//	for ()
	//	{
	//		//if queue front = t_endCell
	//		if()
	//		{
	//			//return queue
	//		}
	//		//else
	//		else
	//		{
	//			//queue front = 
	//			//label cell as explored
	//			//push
	//		}
	//	}

	//	//pop
	//}

	/*return std::vector<int>();*/

	std::vector<bool> visited(m_level.m_tiles.size(), false);
	std::vector<int> parent(m_level.m_tiles.size(), -1);
	std::queue<int> queue;

	visited[t_startCell] = true;
	queue.push(t_startCell);
	int current;

	while (!queue.empty())
	{
		current = queue.front();
		queue.pop();

		if (current == t_endCell)
		{
			break;
		}

		for (int neighboor : m_level.m_tiles.at(current).m_neighboors)
		{
			if (!visited[neighboor])
			{
				visited[neighboor] = true;
				queue.push(neighboor);
			}
		}
	}

	return path;
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