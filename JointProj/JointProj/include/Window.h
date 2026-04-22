#pragma once

#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Player.h"
#include "Enemy.h"

class Window
{
public:
	Window();

	std::optional<sf::Event> pollEvent();

	void renderMenu();
	void renderInstructions();
	void renderSettings();

	void renderGameRunning(const Player& t_player, const Enemy& t_enemy, const Level& t_level);						//renders game
	void renderMiniMap(const Player& t_player, const Enemy& t_enemy, const Level& t_level);				//renders MiniMap

	void renderEnemy(const Player& t_player, const Enemy& t_enemy);
	void renderWalls(const Player& t_player, const Level& t_level);

	bool isOpen() const;
	void close();

	sf::RenderWindow &getWindow();
										
private:
	const static int s_screenWidth{ 800 };
	const static int s_screenHeight{ 600 };

	sf::RenderWindow m_window;
	float m_FOV{ 3.14159f / 3.0f };
	float m_maxDepth{ 20.0f };
	std::vector<float> m_depthBuffer;
	std::vector<float> m_floorBuffer;

	//temp menu stuff
	sf::Texture m_menuTexture;
	sf::Sprite m_menuSprite{ m_menuTexture };
	sf::Texture m_instructionsTexture;
	sf::Sprite m_instructionsSprite{ m_instructionsTexture };
	sf::Texture m_settingsTexture;
	sf::Sprite m_settingsSprite{ m_settingsTexture };
};