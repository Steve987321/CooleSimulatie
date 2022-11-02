#pragma once

namespace sim
{

class Square
{
private:

	std::string m_name = "square ";

	sf::Vector2f m_velocity = {};

	float m_density = 0.1f; 
	float m_temperature = 0.1f;

public:
	sf::RectangleShape Shape;

public:
	Square() { Shape.setSize(sf::Vector2f(10, 10)); Shape.setOutlineColor(sf::Color(255, 255, 255)); }
	Square(const sf::Vector2f& vec) { Shape.setSize(vec); }

	void set_color(const sf::Color& col);

	void set_name(std::string_view name);
	std::string get_name() const;

	//void update_pos();
};

}

