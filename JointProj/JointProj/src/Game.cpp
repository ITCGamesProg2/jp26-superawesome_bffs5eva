#include "../include/Game.h"

Game::Game() : m_window{}, m_DELETEexitGame{ false } //when true game will exit
{
	setupTexts(); // load font 
	setupSprites(); // load texture
	setupAudio(); // load sounds

	m_level.loadLevel(1);
	m_enemy.init(m_level.getWidth(), { 7.0f, 13.0f });

	m_button1.setSize({ 544, 176 });
	m_button1.setPosition({ 128, 16 });

	m_button2.setSize({ 544, 176 });
	m_button2.setPosition({ 128, 208 });

	m_button3.setSize({ 544, 176 });
	m_button3.setPosition({ 128, 400 });
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
			update(timePerFrame); //60 fps
		}
	}
}

void Game::processEvents()
{
	while (const std::optional newEvent = m_window.pollEvent())
	{
		if ( newEvent->is<sf::Event::Closed>()) //close window message 
		{
			m_DELETEexitGame = true;
		}
		else if (newEvent->is<sf::Event::KeyPressed>()) //user pressed a key
		{
			processKeys(newEvent);
		}
		else if (newEvent->is<sf::Event::MouseButtonPressed>())
		{
			processMouseClick(newEvent);
		}
	}
}

void Game::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed *newKeypress = t_event->getIf<sf::Event::KeyPressed>();

	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		if (m_gameState == States::GAME_RUNNING)
		{
			m_gameState = States::GAME_PAUSE;
		}
		else if (m_gameState != States::GAME_MENU)
		{
			m_gameState = States::GAME_MENU;
		}
		else
		{
			m_DELETEexitGame = true;
		}
	}
}

void Game::processMouseClick(const std::optional<sf::Event> t_event)
{
	auto mouseClick = t_event->getIf<sf::Event::MouseButtonPressed>();

	switch (m_gameState)
	{
	case States::GAME_MENU:
		if (m_button1.getGlobalBounds().contains({ static_cast<float>(mouseClick->position.x), static_cast<float>(mouseClick->position.y) }))
		{
			m_gameState = States::GAME_RUNNING;
		}
		else if (m_button2.getGlobalBounds().contains({ static_cast<float>(mouseClick->position.x), static_cast<float>(mouseClick->position.y) }))
		{
			m_gameState = States::GAME_INSTRUCTIONS;
		}
		else if (m_button3.getGlobalBounds().contains({ static_cast<float>(mouseClick->position.x), static_cast<float>(mouseClick->position.y) }))
		{
			m_gameState = States::GAME_SETTINGS;
		}
		break;
	case States::GAME_INSTRUCTIONS:
	case States::GAME_SETTINGS:
		if (m_button1.getGlobalBounds().contains({ static_cast<float>(mouseClick->position.x), static_cast<float>(mouseClick->position.y) }))
		{
			m_gameState = States::GAME_MENU;
		}
		break;
	default:
		break;
	}
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
		break;
	case States::GAME_INSTRUCTIONS:
		m_window.renderInstructions();
		break;
	case States::GAME_SETTINGS:
		m_window.renderSettings();
		break;
	case States::GAME_RUNNING:
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
	default:
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