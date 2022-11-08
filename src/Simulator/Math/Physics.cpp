#include "pch.h"
#include "Physics.h"
#include "./Simulator/Sim.h"
#include <imgui/imgui.h>

float* sim::physics::calc_dichtheid(float current_density[])
{
	// vars
	const float change = 1.0f;

	float new_density_array[100/*sim::grid::rows.x * sim::grid::rows.y*/];
	
	//next_density = (current_density + change * average_density) / (1 + change);
	// 
	// get new density
	for (int i = 0; i < 4; i++)
	{
		float density_array[100/*sim::grid::rows.x * sim::grid::rows.y*/];
		for (int j = 0; j < 100/*sim::grid::rows.x * sim::grid::rows.y*/; j++)
		{
			density_array[j] = (current_density[j] + change * get_average(j, new_density_array)) / (1 + change);
		}
		std::copy(std::begin(density_array), std::end(density_array), std::begin(new_density_array));
	}

	return new_density_array;
}

float get_average(int index, float density[])
{
	index = index + 1;
	float avrage = 0.0f;
	int side[1];

	if (index == 1) { side[0] = 2; side[1] = 11; }

	else if (index == 91) { side[0] = 92; side[1] = 81; }

	else if (index == 10) { side[0] = 9; side[1] = 20; }

	else if (index == 100) { side[0] = 99; side[1] = 90; }

	else if (index % 10 == 1)
	{
		side[0] = index + 1; side[1] = index + 10; side[2] = index - 10;
	}

	else if (index % 10 == 0)
	{
		side[0] = index - 1; side[1] = index - 10; side[2] = index + 10;
	}

	else if (index < 10)
	{
		side[0] = index - 1; side[1] = index + 1; side[2] = index + 10;
	}

	else if (index > 91)
	{
		side[0] = index - 1; side[1] = index + 1; side[2] = index - 10;
	}

	else
	{
		side[0] = index - 1; side[1] = index + 1; side[2] = index + 10; side[3] = index - 10;
	}

	for (int i = 0; i < IM_ARRAYSIZE(side); i++)
	{
		avrage += density[side[i] - 1];
	}
	return avrage / IM_ARRAYSIZE(side);
}


