#include "pch.h"
#include <EngineCore.h>
#include <engine/Engine.h>

#include "ui/ui.h"

int main()
{
	Toad::Engine engine;

#ifdef TOAD_EDITOR
	engine.SetEngineUI(ui::render_ui);
#endif

	if (!engine.Init())
		return EXIT_FAILURE;

	engine.Run();

	return EXIT_SUCCESS;
}