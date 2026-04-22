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

#include "BulletManager.h"

#include "Player.h"

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
	void checkKeyboardState();
									
	void spawnEnemy();				//spawns in an enemy
	void checkCollision();			//runs all collision checks

	void gameOver();				//deals with when game finishes

	Window m_window;
	Level m_level;

	Player m_player;

	Bullet m_bullet;
	BulletManager m_bulletManager;

	//bool to stop door opening and closing rappidly and bullets firing to often. Prevents opening doors at the same time as firing
	bool buttonDown = false;

	sf::Font m_jerseyFont;// font used by message
	
	sf::SoundBuffer m_DELETEsoundBuffer; // buffer for beep sound
	sf::Sound m_DELETEsound{ m_DELETEsoundBuffer }; // sound object to play
	bool m_DELETEexitGame; // control exiting game
};

#pragma warning( pop ) 
#endif // !GAME_HPP