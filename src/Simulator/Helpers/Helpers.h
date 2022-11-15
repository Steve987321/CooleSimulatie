#pragma once

#include <SFML/Graphics/Color.hpp>
#include <imgui/imgui.h>

namespace sim
{
	/// @brief fast random number generator with bounds
	/// @return fast int in range (inclusive) 
	inline int rand_int(int min, int max);

	/// @brief fast random number generator with bounds
	/// @return fast float in range (inclusive) 
	inline float rand_float(float min, float max);	

	/// @brief sets the Imgui's vector4 from a float array
	extern void set_ImVec4(void* col, float src[4]);

	/// @brief set a float4 from imvec4
	extern void set_Float4FromVec4(float col[4], void* src);

	/// @brief turn x,y into array index
	/// @return array index
	int IX(int x, int y, int N);

	/// @brief get color inbetween the value 
	/// @param t the distance in between
	extern sf::Color Lerp(const sf::Color& a, const sf::Color& b, float t);
	extern sf::Color Lerp(const ImVec4& a, const ImVec4& b, float t);
}
