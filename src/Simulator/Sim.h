#pragma once

#include "Logger.h"

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

