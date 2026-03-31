#include "Window.h"

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

	for (int x = 0; x < screenWidth; x++)
	{
		float rayAngle = (angle - m_FOV / 2.0f) + ((float)x / screenWidth) * m_FOV;

		float distanceToWall = 0.0f;
		bool hitWall = false;

		float eyeX = cos(rayAngle);
		float eyeY = sin(rayAngle);

		while (!hitWall && distanceToWall < m_maxDepth)
		{
			distanceToWall += 0.05f;

			int testX = (int)(pos.x + eyeX * distanceToWall);
			int testY = (int)(pos.y + eyeY * distanceToWall);

			if (t_level.getTile(testX, testY) == 1)
			{
				hitWall = true;
			}
		}

		distanceToWall *= cos(rayAngle - angle);

		int ceiling = (screenHeight / 2.0) - screenHeight / distanceToWall;
		int floor = screenHeight - ceiling;

		int shade = 255 - (distanceToWall * 20);
		shade = std::max(0, shade);

		sf::RectangleShape wall;
		wall.setSize({ 1, (float)(floor - ceiling) });
		wall.setPosition({ (float)x, (float)ceiling });
		wall.setFillColor(sf::Color(shade, shade, shade));

		m_window.draw(wall);
	}

	m_window.display();
}

bool Window::isOpen() const
{
	return m_window.isOpen();
}

void Window::close()
{
	m_window.close();
}