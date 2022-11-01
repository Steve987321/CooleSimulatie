#include "pch.h"
#include "sim.h"

namespace sim
{

bool Simulator::init_window()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fluid simulator", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(WINDOW_FPS);

	return ImGui::SFML::Init(window);
}

void Simulator::event_handler()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Simulator::Render()
{

	// show ui
	ui::render_ui();

	window.clear(sf::Color::Black); // window bg

	//--------------------draw------------------------//



	// imgui
	ImGui::SFML::Render(window);



	//--------------------draw------------------------//

	window.display();
}

bool Simulator::init()
{
	log_Debug("init");
	if (!init_window()) return false;

	return true;
}

void Simulator::run()
{
	while (window.isOpen())
	{
		// update deltatime
		deltatime = deltaclock.restart();

		// update imgui sfml
		ImGui::SFML::Update(window, deltatime);

		// handle events 
		event_handler();

		// render the window and contents
		Render();
	}
	clean_up();
}

void Simulator::clean_up()
{
	log_Debug("clean up");
	ImGui::SFML::Shutdown();
	window.close();
}

}