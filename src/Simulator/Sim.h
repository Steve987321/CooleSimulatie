#pragma once

// IMGUI
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

// SFML
#include "SFML/Graphics.hpp"

// SIM
#include "Logger/Logger.h"
#include "Grid\Square.h"
#include "Grid\Grid.h"
#include "ui/ui.h"
#include "Helpers/Helpers.h"
#include "Math/Physics.h"
#include "Types.h"

#define WINDOW_FPS 60
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

namespace sim
{
	class Simulator
	{
	private:
		sf::RenderWindow window;
		sf::Clock deltaclock;

	private:
		std::thread input_thread;

	private:
		std::atomic_bool is_running = false;
		sf::Vector2i mouse_pos = { };

		bool can_interact = false;
		bool is_effector_button_down = false;
		bool is_add_density_button_down = false;
	private:
		bool init_window();
		void event_handler();
		void Render();
		void update_vars();
		void clean_up();
		void get_input();


	public:
		int vel_effector_button = ImGuiKey_MouseLeft;
		int add_density_button = ImGuiKey_MouseRight;

	public:
		sf::Time deltatime;
		int timestep = 2e5;

		sf::Color density;
	public:
		// initialize the simulation
		bool init();

		// rendering and event handling 
		void run();

		// get the window position
		ImVec2 get_windowPos() const;
	};

	inline std::unique_ptr<Simulator> p_Sim;
}

