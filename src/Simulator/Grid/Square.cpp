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

void sim::Square::set_density(float density)
{
	m_density = density;
}
