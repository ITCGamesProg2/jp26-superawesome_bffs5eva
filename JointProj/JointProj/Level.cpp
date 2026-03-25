#include "Level.h"

Level::Level()
{
	loadLevel();
}

void Level::loadLevel()
{
	//cycle through level
	for (int row = 0; row < MAX_ROW; row++)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			switch (m_levelData[row][col])
			{
			case 0:
				m_level[row][col].setSize(sf::Vector2f(width,height));
				m_level[row][col].setPosition(sf::Vector2f(col * width, row * height));
				m_level[row][col].setFillColor(sf::Color::White);
				break;
			case 1:
				m_level[row][col].setSize(sf::Vector2f(width, height));
				m_level[row][col].setPosition(sf::Vector2f(col * width, row * height));
				m_level[row][col].setFillColor(sf::Color::Red);
				break;
			}
		}
	}
}

void Level::draw(sf::RenderWindow &t_window)
{
	for (int row = 0; row < MAX_ROW; row++)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			t_window.draw(m_level[row][col]);
		}
	}
}
