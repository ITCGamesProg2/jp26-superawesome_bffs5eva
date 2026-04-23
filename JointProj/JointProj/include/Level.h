#pragma once

#include <SFML/Graphics.hpp>
#include "yaml-cpp/yaml.h"
#include <exception>

#include <vector>
#include <queue>
#include <string>
#include <iostream>

#include "Door.h"
#include "Item.h"
#include "Key.h"
#include "Collectible.h"

class Player;

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

    std::vector<int> breadthFirstSearch(sf::Vector2f t_startPos, sf::Vector2f t_endPos);
    int asCell(sf::Vector2f t_pos);

    void checkItemPickup(Player& t_player);
    void checkCollision();
    bool isWalkable(int t_type) const;
    int getTileType(int t_x, int t_y) const;

    int getWidth() const;
    int getHeight() const;
    const std::vector<std::unique_ptr<Item>>& getItems() const;

private:
    LevelData m_level;
    std::vector<std::unique_ptr<Item>> m_items;
};