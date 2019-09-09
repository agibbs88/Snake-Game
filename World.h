#pragma once
#include "SFML/Graphics.hpp"
#include "Snake.h"
class World
{
public:
	World(sf::Vector2u l_windowSize);
	~World();

	int GetBlockSize();
	void RespawnApple();
	void SpawnSpecialApple();
	void DestroySpecialApple();
	void Update(Snake& l_player);
	void Render(sf::RenderWindow& l_window);
	void GetWorld();
	void SetWorld(sf::Texture &newWorld);

private:
	sf::Vector2u m_windowSize;
	sf::Vector2i m_item;
	int m_blockSize;
	sf::Texture mapTexture;
	sf::Sprite m_mapBackground;
	sf::CircleShape m_appleShape;
	sf::RectangleShape m_bounds[4];

	sf::Vector2i m_SpecialItem;
	sf::CircleShape m_SpecialApple;
	sf::Image m_Map;
	int m_AppleCount = 0;






};

