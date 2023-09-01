#pragma once

#include "EngineCore.h"

// IMGUI
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

// SFML
#include "SFML/Graphics.hpp"

#include "Logger/Logger.h"
#include "Helpers/Helpers.h"
#include "Types.h"

namespace Toad
{
	class ENGINE_API Engine
	{
	public:
		Engine();
		~Engine();

		using FENGINE_UI = void(*)();

		bool Init();

		void Run();

		// get the window position
		ImVec2 GetWindowPos() const;

		static Engine& Get();

		static Logger& GetLogger();

		sf::Time GetDeltaTime() const;

		void StartGameSession();

		void SetEngineUI(FENGINE_UI p_ui);

	private:
		sf::Time m_deltaTime;

		FENGINE_UI m_renderUI = nullptr;

		sf::RenderWindow m_window;
		sf::Clock m_deltaClock;

	private:
		std::atomic_bool m_isRunning = false;

		bool m_start_game = false;

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