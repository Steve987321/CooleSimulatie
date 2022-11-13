#include "pch.h"
#include "sim.h"

namespace sim
{

bool Simulator::init_window()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fluid simulator", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(WINDOW_FPS);

	for (int i = 0; i < sim::grid::rows.x; i++)
		for (int j = 0; j < sim::grid::rows.y; j++)
		{
			auto square = std::make_unique<Square>(sf::Vector2f(10, 10));

			square->set_name("square (" + std::to_string(sim::grid::gridvec.size() + 1) + ')');
			square->set_color(sf::Color::White);

			square->Shape.setPosition(sf::Vector2f(i * 10, j * 10));

			sim::grid::gridvec.emplace_back(std::move(square)); // it is unique 
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
		{
			log_Ok("closing window");
			window.close();
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
					int selection = -1;

					for (int i = 0; i < sim::grid::gridvec.size(); i++)
					{
						if (sim::grid::gridvec[i]->Shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
						))
						{
							//log_Debug("%d", IX(sim::grid::gridvec[i]->getXpos(), sim::grid::gridvec[i]->getYpos()));
							//log_Debug("%d", i);
							//sim::ui::selected_item_name = sim::grid::gridvec[i]->get_name().c_str();
							strcpy_s(sim::ui::selected_item_name, sim::grid::gridvec[i]->get_name().c_str());
							selection = i;
							break;
						}
					}
					sim::ui::selected_item = selection;
				}
			}
			break;
		}
			
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
		for (int j = 0; j < sim::grid::gridvec.size(); j++)
		{
			sim::p_Grid->Update(i, j);
		}
		window.draw(sim::grid::gridvec[i]->Shape);

		//log_Debug("x: %.2f y: %.2f \n", sim::grid::gridvec[i]->Shape.getPosition().x, sim::grid::gridvec[i]->Shape.getPosition().x);
	}
		

	// imgui
	ImGui::SFML::Render(window);


	//--------------------draw------------------------//

	window.display();
}

void Simulator::update_vars()
{
	//// checks
	//if (sim::p_Sim->isPaused) return;
	//if (sim::p_Sim->previous_timestep == sim::p_Sim->timestep) return;

	//// math
	//float densitys[sim::grid::rows];

	//sim::p_Sim->previous_timestep = sim::p_Sim->timestep;
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

		// calculate vars for the simulations
		update_vars();

		// update imgui sfml
		ImGui::SFML::Update(window, deltatime);

		// handle events 
		event_handler();

		// render the window and contents
		Render();
	}
	clean_up();
}

ImVec2 Simulator::get_windowPos() const
{
	return ImVec2(this->window.getPosition().x, this->window.getPosition().y);
}

void Simulator::clean_up()
{
	log_Debug("clean up");
	ImGui::SFML::Shutdown();
	window.close();
}

}