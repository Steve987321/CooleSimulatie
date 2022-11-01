#include "pch.h"
#include "Simulator/Sim.h"

int main()
{
	sim::p_Sim = std::make_unique<sim::Simulator>();
	sim::p_Log = std::make_unique<sim::Logger>();

	if (!sim::p_Sim->init())
		return EXIT_FAILURE;

	sim::p_Sim->run();

	return EXIT_SUCCESS;
}