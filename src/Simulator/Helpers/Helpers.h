#pragma once
namespace sim
{
	/// @brief make sure min isn't bigger then max
	/// @return fast int in range (inclusive) 
	inline int rand_int(int min, int max);

	/// @brief make sure min isn't bigger then max
	/// @return fast float in range (inclusive) 
	inline float rand_float(float min, float max);	
}
