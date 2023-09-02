#pragma once

#include "EngineMeta.h"
#include "EngineCore.h"

#include <functional>
#include <imgui/imgui_internal.h>

namespace Toad
{
	class ENGINE_API Engine
	{
	public:
		Engine();
		~Engine();

		using FENGINE_UI = std::function<void(ImGuiContext* ctx)>;

		bool Init();

		void Run();

		// get the window position
		sf::Vector2i GetWindowPos() const;

		static Engine& Get();

		static Logger& GetLogger();

		sf::Time GetDeltaTime() const;

		void StartGameSession();

		void SetEngineUI(const FENGINE_UI& p_ui);

	private:
		sf::Time m_deltaTime;
		sf::RenderWindow m_window;
		sf::Clock m_deltaClock;

		FENGINE_UI m_renderUI = nullptr;
		ImGuiIO* m_io = nullptr;

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