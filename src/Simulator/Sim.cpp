#include "pch.h"
#include "sim.h"

namespace sim
{

bool Simulator::init_window()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fluid simulator", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(WINDOW_FPS);

	int size = 0;

	for (int i = 0;i < sim::grid::rows.x;i++)
		for (int j = 0; j < sim::grid::rows.y; j++)
		{
			size++;
			auto square = std::make_unique<Square>(sf::Vector2f(40, 40));

			square->set_name("square (" + std::to_string(size) + ')');
			square->set_color(sf::Color::White);

			square->Shape.setPosition(sf::Vector2f(100 + i * 50, 60 + j * 50));

			sim::grid::gridvec.emplace_back(std::move(square));
		}

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
	

	for (int i = 0; i < sim::grid::gridvec.size(); i++)
	{
		window.draw(sim::grid::gridvec[i]->Shape);
		log_Debug("x: %.2f y: %.2f \n", sim::grid::gridvec[i]->Shape.getPosition().x, sim::grid::gridvec[i]->Shape.getPosition().x);
	}
		

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

		// update vars


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