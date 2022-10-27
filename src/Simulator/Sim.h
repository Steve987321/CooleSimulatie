#pragma once

// IMGUI
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

// SFML
#include "SFML/Graphics.hpp"

// SIM
#include "Logger/Logger.h"

#define WINDOW_FPS 60
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

namespace sim
{
	class Application
	{
	private:
		sf::RenderWindow window;

	private:
		bool init_window();
		void event_handler();
		void clean_up();

	public:
		// initialize the simulation
		bool init();

		// rendering and event handling 
		void run();
	};

}

