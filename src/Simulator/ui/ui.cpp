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
	std::once_flag flag;
	decorations();

	if (ImGui::Begin("Settings"))
	{
		ImDrawList* draw = ImGui::GetWindowDrawList();

		ImGui::Text("FPS %.1f", 1.f / p_Sim->deltatime.asSeconds());

		static float col0[4];
		static float col1[4];

		std::call_once(flag, []()
			{
				sim::set_Float4FromVec4(col0, reinterpret_cast<void*>(&sim::grid::dens0Col));
				sim::set_Float4FromVec4(col1, reinterpret_cast<void*>(&sim::grid::dens1Col));
			});
		
		if (ImGui::SliderInt("timestep", &sim::p_Sim->timestep, 0, 200000));
		{
			// 
		}
		
		if (ImGui::Checkbox("pause timestep", &sim::p_Sim->isPaused)) 
		{
			//
			p_Sim->timestep = 0;
		}

		if (ImGui::ColorEdit4("color 0", col0, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel)) { set_ImVec4(reinterpret_cast<void*>(&sim::grid::dens0Col), col0); }
		if (ImGui::ColorEdit4("color 1", col1, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel)) { set_ImVec4(reinterpret_cast<void*>(&sim::grid::dens1Col), col1); }
		
		draw->AddRectFilledMultiColor(ImGui::GetWindowPos() + ImGui::GetCursorPos(), ImGui::GetWindowPos() + ImGui::GetCursorPos() + ImVec2(ImGui::GetWindowSize().x - 15, 10),
			ImGui::ColorConvertFloat4ToU32(sim::grid::dens0Col),
			ImGui::ColorConvertFloat4ToU32(sim::grid::dens1Col),
			ImGui::ColorConvertFloat4ToU32(sim::grid::dens1Col),
			ImGui::ColorConvertFloat4ToU32(sim::grid::dens0Col)
			);
		ImGui::End();
	}

	if (ImGui::Begin("Inspector"))
	{
		if (sim::grid::gridvec.empty())
			ImGui::BeginDisabled();

		//static int selected_item = -1;
		//static char buf[50];

		ImGui::Text("scene");
		ImGui::Separator();
		ImGui::BeginChild("objects in scene", ImGui::GetWindowSize() / ImVec2(1.08,2) - ImVec2(5,5), true);
		{
			for (int i = 0; i < sim::grid::gridvec.size(); i++)
			{
				const bool is_selected = (i == selected_item);
				if (ImGui::Selectable(sim::grid::gridvec[i]->get_name().c_str(), is_selected))
				{
					strcpy_s(selected_item_name, sim::grid::gridvec[i]->get_name().c_str());
					selected_item = i;
				}
			}
			ImGui::EndChild();
		}

		if (sim::ui::selected_item >= 0) {
			//ImGui::Text(sim::grid::gridvec[selected_item]->get_name().c_str());
			ImGui::BeginChild("current inspected object", ImGui::GetWindowSize() / ImVec2(1.12, 2) - ImVec2(-5, -5), true);
			{
				static float density;

				if (ImGui::InputText("name", selected_item_name, 50))
					sim::grid::gridvec[selected_item]->set_name(selected_item_name);

				/*if (ImGui::SliderFloat("density", &density, 0.0f, 1.0f))
					sim::grid::gridvec[selected_item]->set_density(density);*/

				//if (ImGui::ColorPicker3("color", col))
				//	sim::grid::gridvec[selected_item]->set_color(sf::Color(col[0] * 255, col[1] * 255, col[2] * 255));

				ImGui::EndChild();
			}
		}

		if (sim::grid::gridvec.empty())
			ImGui::EndDisabled();
	}

}
