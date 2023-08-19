#pragma once

#include <SFML/Graphics/Color.hpp>
#include <imgui/imgui.h>

namespace Toad
{
	/// @brief fast random number generator with bounds
	/// @return fast int in range (inclusive) 
	inline int rand_int(int min, int max);

	/// @brief fast random number generator with bounds
	/// @return fast float in range (inclusive) 
	inline float rand_float(float min, float max);	

	/// @brief get color inbetween the value 
	/// @param t the distance in between
	extern sf::Color Lerp(const sf::Color& a, const sf::Color& b, float t);
	extern sf::Color Lerp(const ImVec4& a, const ImVec4& b, float t);
}
