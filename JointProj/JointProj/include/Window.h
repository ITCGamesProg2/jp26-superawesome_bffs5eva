#pragma once

#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Player.h"

class Window
{
public:
	Window();

	std::optional<sf::Event> pollEvent();

	void render(const Player& t_player, const Level& t_level);						//renders game
	void renderMiniMap(const Level& t_level);
	bool isOpen() const;
	void close();
										
private:
	const static int s_screenWidth{ 800 };
	const static int s_screenHeight{ 600 };

	sf::RenderWindow m_window;
	float m_FOV{ 3.14159f / 3.0f };
	float m_maxDepth{ 20.0f };
};