#pragma once

#include <SFML/Graphics.hpp>

class Window
{
public:
	void render();						//renders game
										
private:
	const static int s_screenWidth{ 800 };
	const static int s_screenHeight{ 600 };

	sf::RenderWindow m_window;
};