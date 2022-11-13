#include "pch.h"
#include "Simulator/Sim.h"

int main()
{
	sim::p_Sim = std::make_unique<sim::Simulator>();
	sim::p_Log = std::make_unique<sim::Logger>();
	sim::p_Grid = std::make_unique<sim::Grid>();
	sim::p_Physics = std::make_unique<sim::Physics>();

	if (!sim::p_Sim->init())
		return EXIT_FAILURE;

	sim::p_Sim->run();

	return EXIT_SUCCESS;
}