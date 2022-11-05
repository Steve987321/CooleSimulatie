#include "pch.h"
#include "Physics.h"
#include "./Simulator/Sim.h"

float sim::physics::calc_dichtheid(float current_density[])
{
	// vars
	const float change = 1.0f;

	float new_density_array[100/*sim::grid::rows.x * sim::grid::rows.y*/];
	float next_density;
	
	//next_density = (current_density + change * average_density) / (1 + change);

	// set array items to 0
	for (size_t i = 0; i < sizeof(new_density_array); i++) { new_density_array[i] = 0.0f; }

	// get new density
	for (size_t i = 0; i < 4; i++)
	{
		float density_array[100/*sim::grid::rows.x * sim::grid::rows.y*/];
		for (size_t j = 0; j < 100/*sim::grid::rows.x * sim::grid::rows.y*/; j++)
		{
			//density_array[j] = ;
		}
		//new_density_array = density_array;
	}

	return 0.0f;
}

float get_avrage(int index, float density[])
{
	// vars
	int surrounding_square;
	float avrage_density;

	// calculate surrounding square

	// get density of those square

	// devide sum of density by amount of square

	// return avrage
	return avrage_density;
}
