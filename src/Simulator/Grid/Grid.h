#pragma once
namespace sim::grid
{
	inline const sf::Vector2i rows = sf::Vector2i(50, 50);

	inline std::vector<std::unique_ptr<Square>> gridvec;

	inline ImVec4 dens0Col = { 0, 0, 0, 1 }, dens1Col = {1,1,1,1};
}