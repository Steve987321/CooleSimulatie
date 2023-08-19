#include "pch.h"
#include "Engine/Engine.h"

int main()
{
	Toad::Engine engine;

	if (!engine.Init())
		return EXIT_FAILURE;

	engine.Run();

	return EXIT_SUCCESS;
}