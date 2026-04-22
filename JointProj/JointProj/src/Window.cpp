#include "../include/Window.h"

Window::Window() : m_window(sf::VideoMode({ s_screenWidth, s_screenHeight }), "Game")
{
	m_window.setVerticalSyncEnabled(true);

	if (!m_menuTexture.loadFromFile("Resources\\ASSETS\\IMAGES\\menu.png"))
	{
		std::cout << "problem loading menu texture" << std::endl;
	}

	m_menuSprite.setTexture(m_menuTexture, true);

	if (!m_instructionsTexture.loadFromFile("Resources\\ASSETS\\IMAGES\\instructions.png"))
	{
		std::cout << "problem loading instructions texture" << std::endl;
	}

	m_instructionsSprite.setTexture(m_instructionsTexture, true);

	if (!m_settingsTexture.loadFromFile("Resources\\ASSETS\\IMAGES\\settings.png"))
	{
		std::cout << "problem loading settings texture" << std::endl;
	}

	m_settingsSprite.setTexture(m_settingsTexture, true);
}

std::optional<sf::Event> Window::pollEvent()
{
	return m_window.pollEvent();
}

void Window::renderMenu()
{
	m_window.clear();

	m_window.draw(m_menuSprite);

	m_window.display();
}

void Window::renderInstructions()
{
	m_window.clear();

	m_window.draw(m_instructionsSprite);

	m_window.display();
}

void Window::renderSettings()
{
	m_window.clear();

	m_window.draw(m_settingsSprite);

	m_window.display();
}

void Window::renderGameRunning(const Player& t_player, const Enemy& t_enemy, const Level& t_level)
{
	m_window.clear();

	renderWalls(t_player, t_level);
	renderEnemy(t_player, t_enemy);
	renderMiniMap(t_player, t_enemy, t_level);

	m_window.display();
}

void Window::renderEnemy(const Player& t_player, const Enemy& t_enemy)
{
	int screenWidth = m_window.getSize().x;
	int screenHeight = m_window.getSize().y;

	sf::Vector2f playerPos = t_player.getPosition();
	float playerAngle = t_player.getAngle();
	sf::Vector2f enemyPos = t_enemy.getPosition();

	//player to enemy
	float dx = enemyPos.x - playerPos.x;
	float dy = enemyPos.y - playerPos.y;
	float distance = std::sqrt(dx * dx + dy * dy); //calculate distance to enemy
	if (distance < 0.1f) return;

	//angle from player to enemy
	float angleToEnemy = std::atan2(dy, dx);
	//difference between where player is looking and enemy direction
	float angleDiff = angleToEnemy - playerAngle;

	//normalize angle - range [-PI, PI]
	while (angleDiff < -3.14159f) angleDiff = angleDiff + (2.0f * 3.14159f);
	while (angleDiff > 3.14159f) angleDiff = angleDiff - (2.0f * 3.14159f);

	if (std::abs(angleDiff) > m_FOV / 2.0f) return;

	//convert angle difference to screen X position
	float screenX = (angleDiff + m_FOV / 2.0f) / m_FOV * screenWidth;
	int column = static_cast<int>(screenX);
	if (column < 0 || column >= m_depthBuffer.size()) return;
	if (distance > m_depthBuffer[column]) return;

	sf::Sprite sprite = t_enemy.getSprite();

	//calculate size of sprite based on distance
	float size = screenHeight / distance;
	float spriteScreenX = screenX;
	float spriteWidth = size;
	float spriteHeight = size;

	//determine horizontal range on screen where sprite will be drawn
	int drawStartX = (int)(spriteScreenX - spriteWidth / 2.0f);
	int drawEndX = (int)(spriteScreenX + spriteWidth / 2.0f);

	float texXRatio = 0.0f;
	int texX = 0;

	float wallHeight = 0.0f;
	float wallCeiling = 0.0f;
	float wallFloor = 0.0f;

	float visualOffset = 0.0f;
	float spriteTop = 0.0f;

	for (int x = drawStartX; x < drawEndX; x++) //each vertical slice of the sprite
	{
		if ((x < 0 || x >= screenWidth) || (distance > m_depthBuffer[x])) continue;

		//make 1 pixel wide vertical slice from texture
		sf::Sprite slice = t_enemy.getSprite();
		sf::IntRect fullRect = slice.getTextureRect();

		//column of the texture to use
		texXRatio = (float)(x - drawStartX) / spriteWidth;
		texX = (int)(texXRatio * (float)fullRect.size.x);

		int texY = fullRect.position.y;
		int texHeight = fullRect.size.y;

		slice.setTextureRect(sf::IntRect({ fullRect.position.x + texX, texY }, { 1, texHeight }));
		slice.setScale({ 1.0f, spriteHeight / (float)fullRect.size.y });

		//feet on floor
		spriteHeight = screenHeight / distance;

		wallCeiling = (screenHeight / 2.0f) - (screenHeight / distance);
		wallFloor = screenHeight - wallCeiling;

		visualOffset = spriteHeight * 0.25f;
		spriteTop = wallFloor - spriteHeight + visualOffset;
		slice.setPosition({ (float)x, spriteTop });

		m_window.draw(slice);

		/*sf::RectangleShape debugLine;
		debugLine.setSize({ (float)screenWidth, 1.0f });
		debugLine.setPosition({ 0.0f, wallFloor });
		debugLine.setFillColor(sf::Color::Green);
		m_window.draw(debugLine);*/
	}
}

void Window::renderWalls(const Player& t_player, const Level& t_level)
{
	int screenWidth = m_window.getSize().x;
	int screenHeight = m_window.getSize().y;

	m_depthBuffer.resize(screenWidth);
	m_floorBuffer.resize(screenWidth);

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

	for (int x = 0; x < screenWidth; x++) //each vertical slice of wall
	{
		//calculate ray angle for this slice
		rayAngle = (angle - m_FOV / 2.0f) + ((float)x / screenWidth) * m_FOV;

		distanceToWall = 0.0f;
		hitWall = false;

		//direction vector for ray
		eyeX = cos(rayAngle);
		eyeY = sin(rayAngle);

		//step forward along ray until wall is hit or max depth reached
		while (!hitWall && distanceToWall < m_maxDepth)
		{
			distanceToWall += 0.05f;

			testX = (int)(pos.x + eyeX * distanceToWall);
			testY = (int)(pos.y + eyeY * distanceToWall);

			if (t_level.getTileType(testX, testY) == 1) //check if ray hit a wall
			{
				hitWall = true;
			}
		}

		distanceToWall *= cos(rayAngle - angle); //correct distortion
		m_depthBuffer[x] = distanceToWall; //store distance in depth buffer

		//calculate wall height on screen
		ceiling = (screenHeight / 2.0) - screenHeight / distanceToWall;
		floor = screenHeight - ceiling;
		m_floorBuffer[x] = floor; //store floor in floor buffer

		shade = 255 - (distanceToWall * 20); //shading based on distance
		shade = std::max(0, shade);

		//create verticle slice
		sf::RectangleShape wall;
		wall.setSize({ 1, (float)(floor - ceiling) });
		wall.setPosition({ (float)x, (float)ceiling });
		wall.setFillColor(sf::Color(shade, shade, shade));

		m_window.draw(wall);
	}
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

sf::RenderWindow &Window::getWindow()
{
	return m_window;
}