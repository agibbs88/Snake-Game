#include "Game.h"
#include <iostream>

Game::Game() : m_window("Snake", sf::Vector2u(1280, 720)), m_snake(m_world.GetBlockSize(), &m_textbox), m_world(sf::Vector2u(1280, 720))
{
	m_clock.restart();
	srand(static_cast<unsigned int>(time(nullptr)));
	m_textbox.Setup(5, 14, 150, sf::Vector2f(225, 0));
	m_elapsed = 0.0f;
	m_backGroundMusic.openFromFile("kubate.ogg");
	m_backGroundMusic.setLoop(true);
	m_backGroundMusic.play();
}

Game::~Game() 
{
}

sf::Time Game::GetElapsed()
{
	return m_clock.getElapsedTime();
}
void Game::RestartClock()
{ 
	m_elapsed += m_clock.restart().asSeconds();
}
Window* Game::GetWindow() 
{ 
	return &m_window; 
}

void Game::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& m_snake.GetPhysicalDirection() != Direction::Down)
	{
		m_snake.SetDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& m_snake.GetPhysicalDirection() != Direction::Up) 
	{
		m_snake.SetDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&& m_snake.GetPhysicalDirection() != Direction::Right) 
	{
		m_snake.SetDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& m_snake.GetPhysicalDirection() != Direction::Left)
	{
		m_snake.SetDirection(Direction::Right); 
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_textbox.Clear();
		m_world.RespawnApple();
		m_world.DestroySpecialApple();
		m_snake.Reset();
		m_world.GetWorld();
	}
}

void Game::Update()
{
	m_window.Update();
	float timestep = 1.0f / m_snake.GetSpeed();
	if (m_elapsed >= timestep) 
	{
		m_snake.Tick();
		m_world.Update(m_snake);
		m_elapsed -= timestep;

		if (m_snake.HasLost() == true) 
		{
			m_textbox.Clear();
			m_textbox.Add("GAME OVER! \tScore: " + std::to_string((unsigned long)m_snake.GetScore()));
			m_textbox.AdditoinalBox("Press R to reset game");
		}

		if (m_snake.Win() == true)
		{
			m_textbox.AdditoinalBox("LEVEL 2");
			sf::Texture newWorld;
			newWorld.loadFromFile("World2.png");			
			m_world.SetWorld(newWorld); //Sets up new world to load	
		}
	}
}

void Game::Render()
{
	m_window.BeginDraw();
	m_world.Render(*m_window.GetRenderWindow());
	m_snake.Render(*m_window.GetRenderWindow());
	m_textbox.Render(*m_window.GetRenderWindow());
	m_window.EndDraw();
}