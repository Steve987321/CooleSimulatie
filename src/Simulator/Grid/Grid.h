#pragma once
namespace sim
{
	namespace grid {
		
		constexpr int size = 70;
		constexpr int scale = 8;
		constexpr float dt = 0.2f;
		constexpr float diff = 0;
		constexpr float visc = 0.0000001f;

		//inline const sf::Vector2i rows = sf::Vector2i(size, size);

		inline int mode = 0;
		inline ImVec4 dens0Col = { 0,0,0, 1 }, dens1Col = {1,1,1,1};
		inline std::vector<std::unique_ptr<Square>> gridvec;

	}

	class Grid
	{
	private:
		static const int size = sim::grid::size;

		float dt	= sim::grid::dt;
		float diff	= sim::grid::diff; 
		float visc	= sim::grid::visc;

		float px[size * size] = { 0 };
		float py[size * size] = { 0 };

		float x[size * size] = { 0 };
		float y[size * size] = { 0 };

		float previousDensity[size * size] = { 0 };
		float density[size * size] = { 0 };

	private:
		// gebruikt je alleen voor de visualizering van de velocity in grid
		float MapToRange(float value, float minIn, float maxIn, float minOut, float maxOut);

		// de physics class toepassen op de grid
		void apply_physics();

		// neem langzaam density af voor de hele grid
		void FadeDensity(int size);

	public:
		void AddDensity(float x, float y, float amount);
		void AddVelocity(float x, float y, float px, float py);

		/// @brief update the grid squares variables
		void Update(sf::RenderWindow& win);
		
		sf::Color Hsv(int hue, float sat, float val, float d);
	};

	inline std::unique_ptr<Grid> p_Grid;
}

