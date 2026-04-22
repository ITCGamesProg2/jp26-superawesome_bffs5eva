#ifndef GAME_HPP
#define GAME_HPP
#pragma warning( push )
#pragma warning( disable : 4275 )
// ignore this warning
// C:\SFML - 3.0.0\include\SFML\System\Exception.hpp(41, 47) : 
// warning C4275 : non dll - interface class 'std::runtime_error' used as base for dll - interface class 'sf::Exception'

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include "Window.h"
#include "Level.h"

#include "Player.h"
#include "Enemy.h"

enum class States
{
	GAME_MENU, GAME_INSTRUCTIONS, GAME_SETTINGS, GAME_RUNNING, GAME_PAUSE, GAME_WIN, GAME_LOSE
};

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
	void processEvents();
	void processKeys(const std::optional<sf::Event> t_event);
	void processMouseClick(const std::optional<sf::Event> t_event);
									
	void spawnEnemy();				//spawns in an enemy
	void checkCollision();			//runs all collision checks

	void gameOver(bool t_loss);				//deals with when game finishes

	Window m_window;
	Level m_level;
	States m_gameState{ States::GAME_MENU };

	sf::RectangleShape m_button1;
	sf::RectangleShape m_button2;
	sf::RectangleShape m_button3;

	Player m_player;
	Enemy m_enemy;

	sf::Font m_jerseyFont;// font used by message
	
	sf::SoundBuffer m_DELETEsoundBuffer; // buffer for beep sound
	sf::Sound m_DELETEsound{ m_DELETEsoundBuffer }; // sound object to play
	bool m_DELETEexitGame; // control exiting game
};

#pragma warning( pop ) 
#endif // !GAME_HPP