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

std::once_flag flag, flag2;

void sim::ui::render_ui()
{
	decorations();

	static bool listen_to_hotkey = false;
	static const char* add_density_button_c = ImGui::GetKeyName(ImGuiKey(p_Sim->add_density_button));
	static const char* vel_effector_button_c = ImGui::GetKeyName(ImGuiKey(p_Sim->vel_effector_button));
	
	std::call_once(flag2, []()
		{
			ImGui::SetNextWindowSize(ImVec2(340, 600));
			ImGui::SetNextWindowPos(ImVec2(560, 0));
		});
	if (ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings))
	{
		if (listen_to_hotkey)
		{
			for (int i = 0; i < ImGuiKey_COUNT; i++)
			{
				if (ImGui::IsKeyReleased(ImGuiKey(i)))
				{
					if (ImGuiKey(i) == sf::Keyboard::Escape)
					{
						if (strcmp(add_density_button_c, "...") == 0)
						{
							p_Sim->add_density_button = sf::Keyboard::Unknown;
							add_density_button_c = "None";
						}
						else
						{
							p_Sim->vel_effector_button = sf::Keyboard::Unknown;
							vel_effector_button_c = "None";
						}
					}
					else
					{
						if (strcmp(add_density_button_c, "...") == 0)
						{
							p_Sim->add_density_button = i;
							add_density_button_c = ImGui::GetKeyName(ImGuiKey(i));
						}
						else
						{
							p_Sim->vel_effector_button = i;
							vel_effector_button_c = ImGui::GetKeyName(ImGuiKey(i));
						}
					}
					listen_to_hotkey = false;
					break;
				}
			}
		}
	
		ImDrawList* draw = ImGui::GetWindowDrawList();

		ImGui::Text("FPS %.1f", 1.f / p_Sim->deltatime.asSeconds());
		
		static float col0[4];
		static float col1[4];
		static bool diffdiff = false;

		std::call_once(flag, []()
			{
				sim::set_Float4FromVec4(col0, reinterpret_cast<void*>(&sim::grid::dens0Col));
				sim::set_Float4FromVec4(col1, reinterpret_cast<void*>(&sim::grid::dens1Col));
			});

		ImGui::BeginChild("fluid settings", ImVec2(ImGui::GetWindowSize().x - 15, ImGui::GetWindowSize().y / 3 - 20), true);
		ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - 15);
		ImGui::TextColored(ImVec4(1, 1, 1, 0.2f), "Fluid");
		ImGui::Separator();

		ImGui::SliderFloat("viscosity", &grid::visc, 0.00000001f, 0.00500000f, "%.8f");
		ImGui::SliderFloat("fluid speed", &grid::dt, 0, 1);
		ImGui::SliderFloat("fade dens speed", &grid::fadeDensSpeed, 0.05f, 1);
		if (ImGui::Checkbox("edit diffusion", &diffdiff) && !diffdiff)
			grid::diff = 0;
		if (diffdiff)
			ImGui::SliderFloat("diffusion", &grid::diff, 0.0001f, 0.1f, "%.5f");
		if (ImGui::Button("reset to default"))
		{
			grid::visc = 0.0000001f;
			grid::dt = 0.2f;
			grid::fadeDensSpeed = 0.05f;
			grid::diff = 0;
			diffdiff = false;
		}
		ImGui::EndChild();

		ImGui::BeginChild("visuals", ImVec2(ImGui::GetWindowSize().x - 15, ImGui::GetWindowSize().y / 3 - 20), true);
		ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - 20);
		ImGui::TextColored(ImVec4(1, 1, 1, 0.2f), "Visuals");
		ImGui::Separator();

		ImGui::Combo("Visualization", &sim::grid::mode, gridModes, IM_ARRAYSIZE(gridModes));
		draw->AddRectFilledMultiColor(ImGui::GetWindowPos() + ImGui::GetCursorPos(), ImGui::GetWindowPos() + ImGui::GetCursorPos() + ImVec2(ImGui::GetWindowSize().x - 15, 10),
			ImGui::ColorConvertFloat4ToU32(sim::grid::dens0Col),
			ImGui::ColorConvertFloat4ToU32(sim::grid::dens1Col),
			ImGui::ColorConvertFloat4ToU32(sim::grid::dens1Col),
			ImGui::ColorConvertFloat4ToU32(sim::grid::dens0Col)
			);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
		if (ImGui::ColorEdit3("color 0", col0, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel)) { set_ImVec4(reinterpret_cast<void*>(&sim::grid::dens0Col), col0); }
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 25);
		if (ImGui::ColorEdit3("color 1", col1, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel )) { set_ImVec4(reinterpret_cast<void*>(&sim::grid::dens1Col), col1); }

		ImGui::EndChild();

		ImGui::BeginChild("keybinds", ImVec2(ImGui::GetWindowSize().x - 15, ImGui::GetWindowSize().y / 3 - 20), true);
		ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - 20);
		ImGui::TextColored(ImVec4(1, 1, 1, 0.2f), "Keybinds");
		ImGui::Separator();
		ImGui::Text("Add density"); ImGui::SameLine();
		ImGui::PushID("density");
		if (ImGui::Button(add_density_button_c) && !listen_to_hotkey)
		{
			listen_to_hotkey = true;
			add_density_button_c = "...";
		}
		ImGui::PopID();

		ImGui::Text("Effect velocity"); ImGui::SameLine();
		ImGui::PushID("effector");
		if (ImGui::Button(vel_effector_button_c) && !listen_to_hotkey)
		{
			listen_to_hotkey = true;
			vel_effector_button_c = "...";
		}
		ImGui::PopID();
		ImGui::EndChild();

		ImGui::End();
	}
}
