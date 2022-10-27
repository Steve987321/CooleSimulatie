#include "pch.h"
#include "sim.h"

namespace sim
{

bool Application::init_window()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "sim", sf::Style::Titlebar | sf::Style::Close);

	window.setFramerateLimit(WINDOW_FPS);

	return ImGui::SFML::Init(window);
}

void Application::event_handler()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

bool Application::init()
{
	log_Debug("init");
	if (!init_window()) return false;

	return true;
}

void Application::run()
{
	while (window.isOpen())
	{
		event_handler();
		//onRender(); 
	}
	clean_up();
}

void Application::clean_up()
{
	log_Debug("clean up");
	window.close();
}

}