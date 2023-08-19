#pragma once

// IMGUI
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

// SFML
#include "SFML/Graphics.hpp"

// SIM
#include "Logger/Logger.h"
#include "ui/ui.h"
#include "Helpers/Helpers.h"
#include "Types.h"

namespace Toad
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		// initialize the simulation
		bool Init();

		// rendering and event handling 
		void Run();

		// get the window position
		ImVec2 GetWindowPos() const;

		static Engine& Get();

		static Logger& GetLogger();

		sf::Time GetDeltaTime() const;

	private:
		sf::Time m_deltaTime;

		sf::RenderWindow m_window;
		sf::Clock m_deltaClock;

	private:
		std::atomic_bool m_isRunning = false;

		inline static Engine* s_Instance = nullptr;
		inline static Logger s_LoggerInstance;

	private:
		bool init_window();
		void event_handler();
		void Render();
		void clean_up();
	};
}


#define log_Ok(msg, ...) Toad::Engine::GetLogger().Print(Toad::Logger::log_type::LOK, msg, __VA_ARGS__) 
#define log_Debug(msg, ...) Toad::Engine::GetLogger().Print(Toad::Logger::log_type::LDEBUG, msg, __VA_ARGS__)
#define log_Error(msg, ...) Toad::Engine::GetLogger().Print(Toad::Logger::log_type::LERROR, msg, __VA_ARGS__) 
#define log_Warn(msg, ...) Toad::Engine::GetLogger().Print(Toad::Logger::log_type::LWARNING, msg, __VA_ARGS__) 