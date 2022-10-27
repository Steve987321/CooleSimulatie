#pragma once

// SIM
#include "Logger/Logger.h"

// IMGUI
#include <imgui.h>

// SFML
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

namespace sim
{
	class Application
	{
	private:
		bool init_sfml_window();
	public:
		bool init();
		void run();
		void clean_up();
	};

}

