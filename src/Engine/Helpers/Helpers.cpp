#include "pch.h"
#include "Helpers.h"

namespace Toad
{
	int rand_int(int min, int max)
	{
		if (min > max) min = max;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(min, max);
		return dis(gen);
	}
	float rand_float(float min, float max)
	{
		if (min > max) min = max;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(min, max);
		return dis(gen);
	}
	void set_ImVec4(void* dst, float src[4])
	{
		auto col = reinterpret_cast<ImVec4*>(dst);
		col->x = src[0];
		col->y = src[1];
		col->z = src[2];
		col->w = src[3];
	}
	void set_Float4FromVec4(float col[4], void* src)
	{
		auto vec_col = reinterpret_cast<ImVec4*>(src);
		col[0] = vec_col->x;
		col[1] = vec_col->y;
		col[2] = vec_col->z;
		col[3] = vec_col->w;
	}

	int IX(int x, int y, int N)
	{
		return y * N + x;
	}

	sf::Color Lerp(const sf::Color& a, const sf::Color& b, float val)
	{
		val /= 255;

		return sf::Color(
			(a.r + b.r) * val, 
			(a.g + b.g) * val,
			(a.b + b.b) * val
			);
	}	

	sf::Color Lerp(const ImVec4& a, const ImVec4& b, float val)
	{
		val /= 100;
		
		return sf::Color(
			(a.x + b.x) * val * 255 > 255 ? 255 : (a.x + b.x) * val * 255,
			(a.y + b.y) * val * 255 > 255 ? 255 : (a.y + b.y) * val * 255,
			(a.z + b.z) * val * 255 > 255 ? 255 : (a.z + b.z) * val * 255
			);
	}
}