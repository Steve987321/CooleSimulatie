#include "pch.h"
#include "Helpers.h"
#include <imgui/imgui.h>

namespace sim
{
	int rand_int(int min, int max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(min, max);
		return dis(gen);
	}
	float rand_float(float min, float max)
	{
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
		if (x < 0) { x = 0; }
		if (x > N - 1) { x = N - 1; }

		if (y < 0) { y = 0; }
		if (y > N - 1) { y = N - 1; }
		return (y * N) + x;
	}
}