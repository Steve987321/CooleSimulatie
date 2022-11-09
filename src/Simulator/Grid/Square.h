#pragma once

namespace sim
{

class Square
{
private:

	std::string m_name = "";

	sf::Vector2f m_velocity = {};

	float m_density = 0.1f; 
	float m_temperature = 0.1f; 

	int m_x=0, m_y=0;
public:
	sf::RectangleShape Shape;

public:
	Square() { Shape.setSize(sf::Vector2f(10, 10)); Shape.setOutlineColor(sf::Color(255, 255, 255)); }
	Square(const sf::Vector2f& vec) { Shape.setSize(vec); }

public:
	void set_color(const sf::Color& col);
	void set_name(std::string_view name);
	void set_density(float density);
	void set_truePos(const sf::Vector2i& pos);

	std::string get_name() const;
	int getXpos() const;
	int getYpos() const;

	//void update_pos();
};

}

