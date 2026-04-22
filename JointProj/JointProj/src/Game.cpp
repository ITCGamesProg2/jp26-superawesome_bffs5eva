#include "../include/Game.h"

Game::Game() : m_window{}, m_DELETEexitGame{ false } //when true game will exit
{
	setupTexts(); // load font 
	setupSprites(); // load texture
	setupAudio(); // load sounds

	m_level.loadLevel(1);
	m_enemy.init(m_level.getWidth(), { 7.0f, 13.0f });

	m_playButton.setSize({ 544, 176 });
	m_playButton.setPosition({ 128, 16 });

	m_instructionsButton.setSize({ 544, 176 });
	m_instructionsButton.setPosition({ 128, 208 });

	m_settingsButton.setSize({ 544, 176 });
	m_settingsButton.setPosition({ 128, 400 });

	m_backButton.setSize({ 544, 176 });
	m_backButton.setPosition({ 128, 16 });
}

Game::~Game()
{
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}

		//m_window.render(m_player, m_enemy, m_level); // as many as possible
	}
}

void Game::processEvents()
{
	while (const std::optional newEvent = m_window.pollEvent())
	{
		if ( newEvent->is<sf::Event::Closed>()) // close window message 
		{
			m_DELETEexitGame = true;
		}
		if (newEvent->is<sf::Event::KeyPressed>()) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}

void Game::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed *newKeypress = t_event->getIf<sf::Event::KeyPressed>();

	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_DELETEexitGame = true; 
	}
}

void Game::checkKeyboardState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_DELETEexitGame = true; 
	}
}

void Game::processMouseClick()
{
	bool mouseIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

	if (mouseIsPressed && !m_mouseWasPressed)
	{
		switch (m_gameState)
		{
		case States::GAME_MENU:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				sf::Vector2i mouseClick = sf::Mouse::getPosition(m_window.getWindow());

				if (m_playButton.getGlobalBounds().contains({ static_cast<float>(mouseClick.x), static_cast<float>(mouseClick.y) }))
				{
					m_gameState = States::GAME_RUNNING;
				}
				else if (m_instructionsButton.getGlobalBounds().contains({ static_cast<float>(mouseClick.x), static_cast<float>(mouseClick.y) }))
				{
					m_gameState = States::GAME_INSTRUCTIONS;
				}
				else if (m_settingsButton.getGlobalBounds().contains({ static_cast<float>(mouseClick.x), static_cast<float>(mouseClick.y) }))
				{
					m_gameState = States::GAME_SETTINGS;
				}
			}
			break;
		case States::GAME_INSTRUCTIONS:
		case States::GAME_SETTINGS:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				sf::Vector2i mouseClick = sf::Mouse::getPosition(m_window.getWindow());

				if (m_backButton.getGlobalBounds().contains({ static_cast<float>(mouseClick.x), static_cast<float>(mouseClick.y) }))
				{
					m_gameState = States::GAME_MENU;
				}
			}
		}
	}

	m_mouseWasPressed = mouseIsPressed;
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_DELETEexitGame)
	{
		m_window.close();
	}

	switch (m_gameState)
	{
	case States::GAME_MENU:
		m_window.renderMenu();
		processMouseClick();
		break;
	case States::GAME_SETTINGS:
		processMouseClick();
		break;
	case States::GAME_INSTRUCTIONS:
		processMouseClick();
		break;
	case States::GAME_RUNNING:
		checkKeyboardState();

		m_player.handleInput(t_deltaTime.asMilliseconds(), m_level);
		m_enemy.update(t_deltaTime.asMilliseconds(), m_level,
			(m_level.asCell(m_player.getPosition()) == m_level.asCell(m_enemy.getPosition())),
			m_level.breadthFirstSearch(m_enemy.getPosition(), m_player.getPosition()),
			m_player.getPosition());

		if (!(m_player.getHealth() > 0))
		{
			gameOver(true);
		}

		m_window.renderGameRunning(m_player, m_enemy, m_level);

		break;
	case States::GAME_WIN:
		break;
	case States::GAME_LOSE:
		break;
	}
}

void Game::spawnEnemy()
{
}

void Game::checkCollision()
{
}

void Game::gameOver(bool t_loss)
{
	if (t_loss)
	{
		m_gameState = States::GAME_LOSE;
	}
	else
	{
		m_gameState = States::GAME_WIN;
	}

	//calculate score
}

void Game::setupTexts()
{
	if (!m_jerseyFont.openFromFile("Resources\\ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	/*m_DELETEwelcomeMessage.setFont(m_jerseyFont);
	m_DELETEwelcomeMessage.setString("SFML Game");
	m_DELETEwelcomeMessage.setPosition(sf::Vector2f{ 205.0f, 240.0f });
	m_DELETEwelcomeMessage.setCharacterSize(96U);
	m_DELETEwelcomeMessage.setFillColor(sf::Color::Red);
	m_DELETEwelcomeMessage.setOutlineColor(sf::Color::Black);
	m_DELETEwelcomeMessage.setOutlineThickness(2.0f);*/
}

void Game::setupSprites()
{
	//if (!m_DELETElogoTexture.loadFromFile("Resources\\ASSETS\\IMAGES\\SFML-LOGO.png"))
	//{
	//	std::cout << "problem loading logo" << std::endl;
	//}
	//
	//m_DELETElogoSprite.setTexture(m_DELETElogoTexture,true);// to reset the dimensions of texture
	//m_DELETElogoSprite.setPosition(sf::Vector2f{ 150.0f, 50.0f });
}

void Game::setupAudio()
{
	if (!m_DELETEsoundBuffer.loadFromFile("Resources\\ASSETS\\AUDIO\\beep.wav"))
	{
		std::cout << "Error loading beep sound" << std::endl;
	}
	//m_DELETEsound.play(); // test sound
}