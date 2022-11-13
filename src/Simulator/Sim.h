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
		int previous_timestep = 0;

	private:
		bool init_window();
		void event_handler();
		void Render();
		void update_vars();
		void clean_up();

	public:
		sf::Time deltatime;
		int timestep = 2e5;

		sf::Color density;
		bool isPaused = false;
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

