#pragma once
namespace sim
{
	namespace grid {
		
		constexpr int size = 50;
		constexpr float dt = 0.2f;
		constexpr float diff = 0;
		constexpr float visc = 0.0000001f;

		inline const sf::Vector2i rows = sf::Vector2i(size, size);

		inline std::vector<std::unique_ptr<Square>> gridvec;

		inline ImVec4 dens0Col = { 0, 0, 0, 1 }, dens1Col = { 1,1,1,1 };
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
		// void InitArr(float arr[], int size); c++: int Arr[10] = { 0 } alle elements 0 

		// gebruikt je alleen voor visualizing velocity in grid
		float MapToRange(float value, float minIn, float maxIn, float minOut, float maxOut);
		void apply_physics();
		void FadeDensity(int size);

	public:
		//Grid();
		//Grid(float dt, float diff, float visc);
		//~Grid();

	public:
		void AddDensity(float x, float y, float amount);
		void AddVelocity(float x, float y, float px, float py);

		void Update(int i,int j);

		sf::Color Hsv(int hue, float sat, float val, float d);
	};

	inline std::unique_ptr<Grid> p_Grid;
}

