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

		can_interact = !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);

		this->is_effector_button_down = ImGui::IsKeyDown(ImGuiKey(this->vel_effector_button));
		this->is_add_density_button_down = ImGui::IsKeyDown(ImGuiKey(this->add_density_button));
		mouse_pos = sf::Mouse::getPosition(window);

		switch (event.type)
		{
			case sf::Event::Closed:
			{
				log_Ok("closing window");
				window.close();
				break;
			}
			
		} // switch event
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

	for (int i = 0; i < grid::size; i++)
		for (int j = 0; j < grid::size; j++)
		{
			auto square = std::make_unique<Square>(sf::Vector2f(grid::scale, grid::scale));

			square->set_name("square (" + std::to_string(sim::grid::gridvec.size() + 1) + ')');
			square->set_color(sf::Color::White);
			square->Shape.setPosition(sf::Vector2f(j * sim::grid::scale, i * sim::grid::scale));

			sim::grid::gridvec.emplace_back(std::move(square)); // it is unique 
		}

	this->is_running = true;

	input_thread = std::thread(&sim::Simulator::get_input, this);

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

	this->is_running = false;
	log_Debug("stopping threads")
	this->input_thread.join();

	log_Debug("shutting down imgui");
	ImGui::SFML::Shutdown();

	log_Debug("closing window");
	window.close();
}

void Simulator::get_input()
{
	while (this->is_running)
	{	
		if (!window.hasFocus() || !can_interact) { std::this_thread::sleep_for(std::chrono::milliseconds(100)); continue; }
		if (this->is_effector_button_down)
		{
			auto mDelta = mouse_pos - sf::Mouse::getPosition(window);
			mDelta *= -1;
			p_Grid->AddVelocity(mouse_pos.y / grid::scale, mouse_pos.x / grid::scale, mDelta.y / 10, mDelta.x / 10);
			ImGui::ResetMouseDragDelta();
		}
		if (this->is_add_density_button_down)
		{
			mouse_pos = sf::Mouse::getPosition(window);
			p_Grid->AddDensity(mouse_pos.y / grid::scale, mouse_pos.x / grid::scale, 200);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

}