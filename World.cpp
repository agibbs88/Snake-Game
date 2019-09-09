#include "World.h"
#include <iostream>
World::World(sf::Vector2u l_windowSize)
{
	GetWorld();
	m_blockSize = 20;
	m_windowSize = l_windowSize;
	RespawnApple();
	m_appleShape.setFillColor(sf::Color::Red);
	m_appleShape.setRadius(m_blockSize / 2);

	m_SpecialApple.setFillColor(sf::Color::Transparent);
	m_SpecialApple.setRadius(m_blockSize / 2);

	//Create boarders around the map
	for (int i = 0; i < 4; ++i)
	{
		m_bounds[i].setFillColor(sf::Color(0, 0, 255, 100));

		if (!((i + 1) % 2))
		{
			m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
		}
		else
		{
			m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
		}

		if (i < 2)
		{ 
			m_bounds[i].setPosition(0, 0);
		}
		else
		{
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
		}
	}
}

World::~World()
{
}

int World::GetBlockSize()
{
	return m_blockSize;
}

void World::RespawnApple()
{
	int maxX = (m_windowSize.x / m_blockSize) - 2;
	int maxY = (m_windowSize.y / m_blockSize) - 2;
	m_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	m_appleShape.setPosition(m_item.x * m_blockSize, m_item.y * m_blockSize);
	m_appleShape.setFillColor(sf::Color::Red);
	


}

void World::SpawnSpecialApple()
{
	int maxX = (m_windowSize.x / m_blockSize) - 2;
	int maxY = (m_windowSize.y / m_blockSize) - 2;
	m_SpecialItem = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	m_SpecialApple.setPosition(m_SpecialItem.x * m_blockSize, m_SpecialItem.y * m_blockSize);
	
}

void World::DestroySpecialApple()
{
	m_SpecialApple.setPosition(0, 0);
	m_SpecialApple.setFillColor(sf::Color::Transparent);
	m_AppleCount = 0;
}

void World::Update(Snake & l_player)
{
	
	if (l_player.GetPosition() == m_item)
	{
		++m_AppleCount;
		l_player.Extend();
		l_player.IncreaseScore();
		l_player.IncreaseSpeed();
		RespawnApple();
		
	}

	if (m_AppleCount == 3)
	{
		m_SpecialApple.setFillColor(sf::Color::Magenta);
		SpawnSpecialApple();
		m_AppleCount = 0; // resets special apple number count.
	}
	if (l_player.GetPosition() == m_SpecialItem)
	{
		l_player.DecreaseSpeed();
		m_SpecialApple.setPosition(0, 0);
		m_SpecialApple.setFillColor(sf::Color::Transparent);

	}
	l_player.ShowScore();
	int gridSize_x = m_windowSize.x / m_blockSize;
	int gridSize_y = m_windowSize.y / m_blockSize;

	// Check for collision with inside walls.
	if (l_player.GetPosition().x == 0 || l_player.GetPosition().y == 0 || l_player.GetPosition().x >= gridSize_x - 1 || l_player.GetPosition().y >= gridSize_y - 1)
	{
		l_player.Lose();
		DestroySpecialApple();
		m_appleShape.setFillColor(sf::Color::Transparent);
	}
}

void World::Render(sf::RenderWindow & l_window)
{
	l_window.draw(m_mapBackground);
	for (int i = 0; i < 4; ++i)
	{
		l_window.draw(m_bounds[i]);
	}
	l_window.draw(m_appleShape);
	l_window.draw(m_SpecialApple);
}

void World::GetWorld()
{
	mapTexture.loadFromFile("world1.jpg");
	m_mapBackground.setTexture(mapTexture);
	m_mapBackground.setPosition(0, 0);
}

void World::SetWorld(sf::Texture &newWorld)
{
	
	//mapTexture = newWorld;
	mapTexture.swap(newWorld);

	
}
