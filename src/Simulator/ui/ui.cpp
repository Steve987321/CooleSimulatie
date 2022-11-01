#include "pch.h"
#include "Simulator/Sim.h"
#include "ui.h"

void sim::ui::decorations()
{
	
}

void sim::ui::render_ui()
{
	decorations();

	if (ImGui::Begin("settings"))
	{

		ImGui::Text("FPS %.1f", 1.f / p_Sim->deltatime.asSeconds());

		ImGui::End();
	}
}
