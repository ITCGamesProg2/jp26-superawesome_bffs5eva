#include "../include/Window.h"

Window::Window() : m_window(sf::VideoMode({ s_screenWidth, s_screenHeight }), "Game")
{
	m_window.setVerticalSyncEnabled(true);
}

std::optional<sf::Event> Window::pollEvent()
{
	return m_window.pollEvent();
}

void Window::render(const Player& t_player, const Level& t_level)
{
	m_window.clear();

	int screenWidth = m_window.getSize().x;
	int screenHeight = m_window.getSize().y;

	auto pos = t_player.getPosition();
	float angle = t_player.getAngle();

	float rayAngle = 0.0f;

	float distanceToWall = 0.0f;
	bool hitWall = false;

	float eyeX = 0.0f;
	float eyeY = 0.0f;

	int testX = 0;
	int testY = 0;

	int ceiling = 0;
	int floor = 0;

	int shade = 0;

	for (int x = 0; x < screenWidth; x++)
	{
		rayAngle = (angle - m_FOV / 2.0f) + ((float)x / screenWidth) * m_FOV;

		distanceToWall = 0.0f;
		hitWall = false;

		eyeX = cos(rayAngle);
		eyeY = sin(rayAngle);

		while (!hitWall && distanceToWall < m_maxDepth)
		{
			distanceToWall += 0.05f;

			testX = (int)(pos.x + eyeX * distanceToWall);
			testY = (int)(pos.y + eyeY * distanceToWall);

			if (t_level.getTileType(testX, testY) == 1)
			{
				hitWall = true;
			}
		}

		distanceToWall *= cos(rayAngle - angle);

		ceiling = (screenHeight / 2.0) - screenHeight / distanceToWall;
		floor = screenHeight - ceiling;

		shade = 255 - (distanceToWall * 20);
		shade = std::max(0, shade);

		sf::RectangleShape wall;
		wall.setSize({ 1, (float)(floor - ceiling) });
		wall.setPosition({ (float)x, (float)ceiling });
		wall.setFillColor(sf::Color(shade, shade, shade));

		m_window.draw(wall);
	}

	renderMiniMap(t_player, t_level);

	m_window.display();
}

void Window::renderMiniMap(const Player& t_player, const Level& t_level)
{
	auto pos = t_player.getPosition();

	sf::RectangleShape tempRect;
	tempRect.setSize(sf::Vector2f{ 5, 5 });
	tempRect.setFillColor(sf::Color::Red);

	for (int col = 0; col < t_level.getHeight(); col++)
	{
		for (int row = 0; row < t_level.getWidth(); row++)
		{
			if (t_level.getTileType(row, col) == 1)
			{
				tempRect.setPosition(sf::Vector2f{ static_cast<float>(20 + (row * 5)), static_cast<float>(20 + (col * 5)) });
				m_window.draw(tempRect);
			}
			else if (row == static_cast<int>(pos.x) && col == static_cast<int>(pos.y)) //draw player location in minimap
			{
				tempRect.setFillColor(sf::Color::Cyan);
				tempRect.setPosition(sf::Vector2f{ static_cast<float>(20 + (row * 5)), static_cast<float>(20 + (col * 5)) });
				m_window.draw(tempRect);
				tempRect.setFillColor(sf::Color::Red);
			}
		}
	}
}

bool Window::isOpen() const
{
	return m_window.isOpen();
}

void Window::close()
{
	m_window.close();
}