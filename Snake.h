#pragma once
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include <vector>
struct SnakeSegment
{
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};
enum class Direction { None, Up, Down, Left, Right };
using SnakeContainer = std::vector<SnakeSegment>;

class Snake 
{
public:
	Snake(float l_blockSize, Textbox* l_log);
	~Snake();

	
	void SetDirection(Direction l_dir);
	Direction GetDirection();
	int GetSpeed();
	sf::Vector2i GetPosition();
	int GetLives();
	int GetScore();
	void IncreaseScore();
	void IncreaseSpeed();
	void DecreaseSpeed();
	bool HasLost();
	void ShowScore();
	void Lose(); 
	void ToggleLost();
	bool Win();

	Direction GetPhysicalDirection();

	void Extend(); 
	void Reset(); 
	void Move(); 
	void Tick(); 
	void Cut(int l_segments);
	void Render(sf::RenderWindow& l_window);
private:
	void CheckCollision(); 
	SnakeContainer m_snakeBody; 
	float m_size;
	Direction m_dir; 
	int m_speed; 
	int m_lives; 
	int m_score; 
	bool m_lost; 
	bool m_Won;
	sf::RectangleShape m_bodyRect; 
	Textbox* m_log;
};

