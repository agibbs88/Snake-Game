#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using MessageContainer = std::vector<std::string>;

class Textbox 
{
public:
	Textbox();
	Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
	~Textbox();

	void Setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
	void Setup2(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
	void Add(std::string l_message);
	void AdditoinalBox(std::string l_Message);
	void Clear();

	void Render(sf::RenderWindow& l_wind);
private:
	MessageContainer m_messages;
	MessageContainer m_messages1;
	int m_numVisible;

	sf::RectangleShape m_backdrop;
	sf::RectangleShape m_backdrop1;
	sf::Font m_font;
	sf::Text m_content;

	sf::Text m_content2;
};