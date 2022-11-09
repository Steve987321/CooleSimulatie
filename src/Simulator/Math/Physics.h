#pragma once

namespace sim
{

namespace physics
{

	/// @brief 
	/// @param verandering 
	/// @param c 
	/// @param n 
	/// @return 
	float* calc_dichtheid(float current_density[], float change);

	float get_average(int index, float density[]);

	/*int IX(int x, int y)
	{
		return x + y * sim::grid::gridvec.size();
	}*/
}

}