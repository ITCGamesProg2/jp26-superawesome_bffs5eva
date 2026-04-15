#pragma once

#include <SFML/Graphics.hpp>
#include "yaml-cpp/yaml.h"
#include <exception>

#include <vector>
#include <queue>
#include <string>
#include <iostream>

#include "Door.h"
#include "Collectible.h"

const static int MAX_NEIGHBOORS = 8;

struct tileData
{
    int m_type;
    std::vector<int> m_neighboors;
};

struct LevelData
{
    int m_width;
    int m_height;

    std::vector<tileData> m_tiles;
};

class Level
{
public:
    Level() = default;
    void loadLevel(int t_levelNr);
    void loadTileNeighboors(int t_index, int t_row, int t_col);

    std::vector<int> breadthFirstSearch(int t_startCell, int t_endCell);

    void checkCollision();
    int getTileType(int t_x, int t_y) const;

    int getWidth() const;
    int getHeight() const;

private:
    LevelData m_level;
};