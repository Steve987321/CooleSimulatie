#pragma once

// SFML
#include "SFML/System.hpp"

// SIM
#include "Logger/Logger.h"

// IMGUI
#include <imgui.h>

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

