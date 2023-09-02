#include "pch.h"

#include "EngineCore.h"

#include "engine.h"

#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

#include "Game/src/game_core/GameBase.h"

namespace Toad
{

Engine::Engine()
{
	s_Instance = this;
}

Engine::~Engine() = default;

bool Engine::Init()
{
	log_Debug("Initializing Engine");

	if (!init_window()) return false;

	m_isRunning = true;

	return true;
}

void Engine::Run()
{
	while (m_window.isOpen())
	{
		// update deltatime
		m_deltaTime = m_deltaClock.restart();

		// update imgui sfml
		ImGui::SFML::Update(m_window, m_deltaTime);

		// handle events 
		event_handler();

		// render the window and contents
		Render();
	}

	clean_up();
}

bool Engine::init_window()
{
#ifdef TOAD_EDITOR
	m_window.create(sf::VideoMode(600, 600), "Engine 2D", sf::Style::Titlebar | sf::Style::Close);
	m_window.setFramerateLimit(60);
	return ImGui::SFML::Init(m_window);
#else
	// TODO: CHENGE DEEZZ
	m_window.create(sf::VideoMode(600, 600), "Game", sf::Style::Titlebar | sf::Style::Close);
	m_window.setFramerateLimit(60);
	return true;
#endif
}

void Engine::event_handler()
{
	sf::Event e;
	while (m_window.pollEvent(e))
	{
		ImGui::SFML::ProcessEvent(e);

		switch (e.type)
		{

		case sf::Event::Closed:
		{
			log_Ok("closing window");
			m_window.close();
			break;
		}

		}
	}
}

void Engine::Render()
{
	// show ui
	m_renderUI();

	m_window.clear(sf::Color::Black); // window bg

	//--------------------draw------------------------//

	// imgui
	ImGui::SFML::Render(m_window);

	//--------------------draw------------------------//

	m_window.display();
}

sf::Vector2i Engine::GetWindowPos() const
{
	return { this->m_window.getPosition().x, this->m_window.getPosition().y };
}

Engine& Engine::Get()
{
	return *s_Instance;
}

Logger& Engine::GetLogger()
{
	return s_LoggerInstance;
}

sf::Time Engine::GetDeltaTime() const
{
	return m_deltaTime;
}

void Engine::StartGameSession()
{
}

void Engine::SetEngineUI(FENGINE_UI p_ui)
{
	m_renderUI = p_ui;
}

void Engine::clean_up()
{
	log_Debug("clean up");

	this->m_isRunning = false;

	log_Debug("shutting down imgui");
	ImGui::SFML::Shutdown();

	log_Debug("closing window");
	m_window.close();
}

}