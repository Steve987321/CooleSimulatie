#pragma once
namespace sim::grid
{
	inline const sf::Vector2i rows = sf::Vector2i(10, 10);

	inline std::vector<std::unique_ptr<Square>> gridvec;
}