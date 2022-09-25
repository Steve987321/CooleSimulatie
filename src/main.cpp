#include "pch.h"

#include "Simulator/Sim.h"

int main()
{
	auto app = std::make_unique<sim::Application>();

	if (!app->init())
		return EXIT_FAILURE;

	app->run();
	app->clean_up();

	return EXIT_SUCCESS;
}