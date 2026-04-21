#include "../include/Window.h"

Window::Window() : m_window(sf::VideoMode({ s_screenWidth, s_screenHeight }), "Game")
{
	m_window.setVerticalSyncEnabled(true);
}

std::optional<sf::Event> Window::pollEvent()
{
	return m_window.pollEvent();
}

void Window::render(const Player& t_player, const Enemy& t_enemy, const Level& t_level)
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

	//draw walls
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

	//draw enemy
	sf::Vector2f playerPos = t_player.getPosition();
	float playerAngle = t_player.getAngle();
	sf::Vector2f enemyPos = t_enemy.getPosition();

	float dx = enemyPos.x - playerPos.x;
	float dy = enemyPos.y - playerPos.y;
	float distance = std::sqrt(dx * dx + dy * dy);

	float angleToEnemy = std::atan2(dy, dx);
	float angleDiff = angleToEnemy - playerAngle;

	while (angleDiff < -3.14159f) angleDiff += 2 * 3.14159f;
	while (angleDiff > 3.14159f) angleDiff -= 2 * 3.14159f;

	if (std::abs(angleDiff) < m_FOV / 2.0f)
	{
		// visible
	}

	float screenX = (angleDiff + m_FOV / 2.0f) / m_FOV * screenWidth;

	float size = screenHeight / distance;

	sf::Sprite sprite = t_enemy.getSprite();

	sprite.setOrigin({ 24.0f, 24.0f }); // half of 48x48
	sprite.setScale({ size / 48.0f, size / 48.0f });

	ceiling = (screenHeight / 2.0f) - size / 2.0f;
	sprite.setPosition({ screenX, ceiling + size / 2.0f });

	m_window.draw(sprite);

	renderMiniMap(t_player, t_enemy, t_level);

	m_window.display();
}

void Window::renderMiniMap(const Player& t_player, const Enemy& t_enemy, const Level& t_level)
{
	auto playerPos = t_player.getPosition();
	auto enemyPos = t_enemy.getPosition();

	sf::RectangleShape tempRect;
	tempRect.setSize(sf::Vector2f{ 5, 5 });
	tempRect.setFillColor(sf::Color::Red);

	for (int col = 0; col < t_level.getHeight(); col++)
	{
		for (int row = 0; row < t_level.getWidth(); row++)
		{
			//draw tiles first
			if (t_level.getTileType(row, col) == 1)
			{
				tempRect.setFillColor(sf::Color::Red);
				tempRect.setPosition({ 20.f + row * 5.f, 20.f + col * 5.f });
				m_window.draw(tempRect);
			}

			//draw enemy
			if (row == (int)enemyPos.x && col == (int)enemyPos.y)
			{
				tempRect.setFillColor(sf::Color::Magenta);
				tempRect.setPosition({ 20.f + row * 5.f, 20.f + col * 5.f });
				m_window.draw(tempRect);
			}

			//draw player
			if (row == (int)playerPos.x && col == (int)playerPos.y)
			{
				tempRect.setFillColor(sf::Color::Cyan);
				tempRect.setPosition({ 20.f + row * 5.f, 20.f + col * 5.f });
				m_window.draw(tempRect);
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