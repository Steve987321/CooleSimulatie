#include "pch.h"
#include "sim.h"

namespace sim
{

bool Simulator::init_window()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fluid simulator", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(WINDOW_FPS);

	for (int i = 0; i < grid::size; i++)
		for (int j = 0; j < grid::size; j++)
		{
			auto square = std::make_unique<Square>(sf::Vector2f(grid::scale, grid::scale));

			square->set_name("square (" + std::to_string(sim::grid::gridvec.size() + 1) + ')');
			square->set_color(sf::Color::White);
			square->Shape.setPosition(sf::Vector2f(j * sim::grid::scale, i * sim::grid::scale));

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
			case sf::Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					this->LMB_down = false;
				if (event.mouseButton.button == sf::Mouse::Right)
					this->RMB_down = false;
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				mouse_pos = sf::Mouse::getPosition(window);
				// LMB pressed
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					this->LMB_down = true;
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
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					this->RMB_down = true;
				}
				
				break;
			}
			
		} // switch event

		//// RMB down
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		//{
		//	p_Grid->AddDensity(currMouse.y / grid::scale, currMouse.x / grid::scale, 200);
		//}
	}
}

void Simulator::Render()
{
	// show ui
	ui::render_ui();

	window.clear(sf::Color::Black); // window bg

	//--------------------draw------------------------//
	
	// update the grid and draw the grid
	sim::p_Grid->Update(window);	


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
	std::once_flag flag;

	this->is_running = true;
	input_thread = std::thread(&sim::Simulator::input, this);

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
	this->is_running = false;
	ImGui::SFML::Shutdown();
	window.close();
}

void Simulator::input()
{
	while (this->is_running)
	{	
		// LMB held
		if (this->LMB_down)
		{
			mouse_pos = sf::Mouse::getPosition(window);
			ImVec2 mDelta = ImGui::GetMouseDragDelta(0, 0);
			p_Grid->AddVelocity(mouse_pos.y / grid::scale, mouse_pos.x / grid::scale, mDelta.y / 10, mDelta.x / 10);
			ImGui::ResetMouseDragDelta();
		}
		if (this->RMB_down)
		{
			mouse_pos = sf::Mouse::getPosition(window);
			p_Grid->AddDensity(mouse_pos.y / grid::scale, mouse_pos.x / grid::scale, 200);
		}

		if (!window.hasFocus()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

}