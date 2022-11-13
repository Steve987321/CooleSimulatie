#pragma once

namespace sim
{

class Square
{
private:
	std::string m_name = "";

	int m_x=0, m_y=0;
public:
	sf::RectangleShape Shape;

public:
	//Square() { Shape.setSize(sf::Vector2f(10,10)); Shape.setOutlineColor(sf::Color(255, 255, 255)); }
	Square(const sf::Vector2f& vec) { Shape.setSize(vec); }

public:
	void set_color(const sf::Color& col);
	void set_name(std::string_view name);

	std::string get_name() const;
	int getXpos() const;
	int getYpos() const;

	//void update_pos();
};

}

