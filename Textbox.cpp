#include "Textbox.h"

Textbox::Textbox() 
{
	Setup(5, 9, 20, sf::Vector2f(0, 0));
	Setup2(5, 9, 20, sf::Vector2f(500, 0));
}

Textbox::Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos)
{
	Setup(l_visible, l_charSize, l_width, l_screenPos);
	Setup2(l_visible, l_charSize, l_width, l_screenPos);
}

Textbox::~Textbox() 
{
	Clear();
}

void Textbox::Setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos)
{
	m_numVisible = l_visible;
	sf::Vector2f l_offset(-3.0f, -3.0f); //Sets text box boundry to screen.d
	m_font.loadFromFile("arial.ttf");
	m_content.setFont(m_font);
	m_content.setString("");
	m_content.setCharacterSize(20);
	m_content.setFillColor(sf::Color::Red);
	m_content.setPosition(l_screenPos + l_offset);

	m_backdrop.setSize(sf::Vector2f(l_width, (l_visible * (l_charSize * 2.0f))));
	m_backdrop.setFillColor(sf::Color(0, 0, 0, 0));
	m_backdrop.setPosition(l_screenPos);
}

void Textbox::Setup2(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos)
{
	sf::Vector2f l_offset(-3.0f, -3.0f);
	m_content2.setFont(m_font);
	m_content2.setString("");
	m_content2.setCharacterSize(20);
	m_content2.setFillColor(sf::Color::Red);
	m_content2.setPosition(l_screenPos + l_offset);

	m_backdrop1.setSize(sf::Vector2f(l_width, (l_visible * (l_charSize * 2.0f))));
	m_backdrop1.setFillColor(sf::Color(0, 255, 0, 0));
	m_backdrop1.setPosition(l_screenPos);
}

void Textbox::Add(std::string l_message) 
{
	m_messages.push_back(l_message);
	if (m_messages.size() < 3) 
	{ 
		return; 
	}
	m_messages.erase(m_messages.begin());
}

void Textbox::AdditoinalBox(std::string l_Message)
{
	m_messages1.push_back(l_Message);
	if (m_messages1.size() <= 1)
	{
		return;
	}
	m_messages1.erase(m_messages1.begin());
}

void Textbox::Clear() 
{ 
	m_messages.clear(); 
	m_messages1.clear();
}

void Textbox::Render(sf::RenderWindow& l_wind)
{
	std::string l_content;
	std::string l_content2;
	for (auto &itr : m_messages) 
	{
		l_content.append(itr + "\t");
	}
	if (l_content != "")
	{
		m_content.setString(l_content);
		l_wind.draw(m_backdrop);
		l_wind.draw(m_content);
	}


	for (auto &itr : m_messages1)
	{
		l_content2.append(itr + "\t");
	}
	if (l_content2 != "")
	{
		m_content2.setString(l_content2);
		l_wind.draw(m_backdrop1);
		l_wind.draw(m_content2);
	}

}