#include "pch.h"
#include "Simulator/Sim.h"
#include "Square.h"

void sim::Square::set_color(const sf::Color& col)
{
	this->Shape.setFillColor(col);
}

void sim::Square::set_name(std::string_view name)
{
	m_name = name;
}

std::string sim::Square::get_name() const
{
	 return m_name; 
}

int sim::Square::getXpos() const
{
	//return this->Shape.getPosition().x;
	return this->m_x;
}

int sim::Square::getYpos() const
{
	//return this->Shape.getPosition().y;
	return this->m_y;
}

void sim::Square::set_density(float density)
{
	m_density = density;
}

void sim::Square::set_truePos(const sf::Vector2i& pos)
{
	m_x = pos.x;
	m_y = pos.y;
}
