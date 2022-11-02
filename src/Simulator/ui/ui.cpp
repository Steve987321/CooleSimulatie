#include "pch.h"
#include "Simulator/Sim.h"
#include "ui.h"

void sim::ui::decorations()
{
	ImGuiStyle* style = &ImGui::GetStyle();

	style->FrameRounding = 3.f;
	style->GrabRounding = 2.f;

	//main colors 21 21 21, 36 36 36, 48 173 228
	ImU32 dark_gray = ImColor(21, 21, 21);
	ImU32 gray = ImColor(36, 36, 36);
	ImU32 light_gray = ImColor(46, 46, 46);
	ImU32 light_blue = ImColor(48, 173, 228);
	ImU32 lighter_blue = ImColor(147, 170, 180);
	ImU32 dark_blue = ImColor(147, 170, 180);
	ImU32 darker_white = ImColor(184, 184, 184);

	style->Colors[ImGuiCol_Button] = (ImColor)gray;
	style->Colors[ImGuiCol_ButtonHovered] = (ImColor)light_gray;
	style->Colors[ImGuiCol_ButtonActive] = ImColor(13, 13, 13);

	style->Colors[ImGuiCol_CheckMark] = (ImColor)light_blue;

	style->Colors[ImGuiCol_FrameBg] = (ImColor)gray;
	style->Colors[ImGuiCol_FrameBgHovered] = (ImColor)gray;
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(13, 13, 13);

	style->Colors[ImGuiCol_TitleBg] = (ImColor)dark_gray;
	style->Colors[ImGuiCol_TitleBgActive] = (ImColor)light_blue;

	style->Colors[ImGuiCol_ScrollbarBg] = ImColor(15, 15, 15);
	style->Colors[ImGuiCol_ScrollbarGrab] = (ImColor)gray;
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = (ImColor)gray;
	style->Colors[ImGuiCol_ScrollbarGrabActive] = (ImColor)gray;

	style->Colors[ImGuiCol_SliderGrab] = (ImColor)gray;
	style->Colors[ImGuiCol_SliderGrabActive] = (ImColor)gray;

	style->Colors[ImGuiCol_Text] = (ImColor)darker_white;

	style->Colors[ImGuiCol_WindowBg] = (ImColor)dark_gray;

	style->Colors[ImGuiCol_HeaderHovered] = ImColor(55, 55, 55);
	style->Colors[ImGuiCol_HeaderActive] = (ImColor)light_gray;
	style->Colors[ImGuiCol_Header] = (ImColor)lighter_blue;
}

void sim::ui::render_ui()
{
	decorations();

	if (ImGui::Begin("Settings"))
	{
		ImGui::Text("FPS %.1f", 1.f / p_Sim->deltatime.asSeconds());

		static bool test = false;
		//ImGui::SliderFloat("timestep", &sim);
		ImGui::Checkbox("checkbox", &test);
		ImGui::End();
	}

	if (ImGui::Begin("Inspector"))
	{
		if (sim::grid::gridvec.empty())
			ImGui::BeginDisabled();

		static int selected_item = -1;
		static char buf[50];

		ImGui::Text("scene");
		ImGui::Separator();
		ImGui::BeginChild("objects in scene", ImGui::GetWindowSize() / ImVec2(2,2) - ImVec2(5,5), true);
		{
			for (int i = 0; i < sim::grid::gridvec.size(); i++)
			{
				const bool is_selected = (i == selected_item);
				if (ImGui::Selectable(sim::grid::gridvec[i]->get_name().c_str(), is_selected))
				{
					strcpy_s(buf, sim::grid::gridvec[i]->get_name().c_str());
					selected_item = i;
				}

			}
			ImGui::EndChild();
		}

		
		//ImGui::Text(sim::grid::gridvec[selected_item]->get_name().c_str());
		ImGui::BeginChild("current inspected object", ImGui::GetWindowSize() / ImVec2(2, 2) - ImVec2(-5, -5), true);
		{
			static float col[3];

			if (ImGui::InputText("name", buf, 50))
				sim::grid::gridvec[selected_item]->set_name(buf);

			if (ImGui::ColorPicker3("color", col))
				sim::grid::gridvec[selected_item]->set_color(sf::Color(col[0] * 255, col[1] * 255, col[2] * 255));

			ImGui::EndChild();
		}


		if (sim::grid::gridvec.empty())
			ImGui::EndDisabled();
	}

}
