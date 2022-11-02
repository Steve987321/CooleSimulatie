#include "pch.h"
#include "Physics.h"

float sim::physics::calc_dichtheid(int x, int y, float current_density, float average_density)
{
	float next_density;
	float change = 1.0f;
	
	next_density = (current_density + change * average_density) / (1 + change);

	return next_density;
}
