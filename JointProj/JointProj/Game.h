#ifndef GAME_HPP
#define GAME_HPP
#pragma warning( push )
#pragma warning( disable : 4275 )
// ignore this warning
// C:\SFML - 3.0.0\include\SFML\System\Exception.hpp(41, 47) : 
// warning C4275 : non dll - interface class 'std::runtime_error' used as base for dll - interface class 'sf::Exception'

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Window.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	void setupTexts();
	void setupSprites();
	void setupAudio();

	void update(sf::Time t_deltaTime);
	void render();

	void processEvents();
	void processKeys(const std::optional<sf::Event> t_event);
	void checkKeyboardState();

	void spawnEnemy();
	void checkCollision();

	void gameOver();

	Window m_windowClass;
	sf::RenderWindow m_window; // main SFML window

	sf::Font m_jerseyFont;// font used by message
	
	sf::SoundBuffer m_DELETEsoundBuffer; // buffer for beep sound
	sf::Sound m_DELETEsound{ m_DELETEsoundBuffer }; // sound object to play
	bool m_DELETEexitGame; // control exiting game
};

#pragma warning( pop ) 
#endif // !GAME_HPP