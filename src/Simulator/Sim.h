#pragma once

#include "Logger/Logger.h"
#include <imgui.h>

namespace sim
{
	class Application
	{
	private:

	public:
		bool init();
		void run();
		void clean_up();
	};

}

