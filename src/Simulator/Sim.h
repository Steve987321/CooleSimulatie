#pragma once

// IMGUI
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

// SFML
#include "SFML/Graphics.hpp"

// SIM
#include "Logger/Logger.h"
#include "ui/ui.h"

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
		bool init_window();
		void event_handler();
		void Render();
		void clean_up();

	public:
		sf::Time deltatime;

	public:
		// initialize the simulation
		bool init();

		// rendering and event handling 
		void run();
	};

	inline std::unique_ptr<Simulator> p_Sim;
}

