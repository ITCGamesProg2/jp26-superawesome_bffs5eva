#pragma once

#include <SFML/Graphics.hpp>
#include "yaml-cpp/yaml.h"
#include <exception>

#include <vector>
#include <string>

#include "Door.h"
#include "Collectible.h"

struct tileData
{
    int m_type;
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

    void checkCollision();
    int getTileType(int t_x, int t_y) const;

private:
    LevelData m_level;
};