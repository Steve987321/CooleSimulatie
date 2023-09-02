#pragma once

namespace Toad
{

	struct ENGINE_API Vec2I
	{
		int x, y;
		Vec2I() : x(0), y(0) {}
		Vec2I(int X, int Y) : x(X), y(Y) {}

		bool operator==(const Vec2I& other) const { return x == other.x && y == other.y; }

		Vec2I operator+(const Vec2I& other) const { return {x + other.x, y + other.y}; }
		Vec2I operator-(const Vec2I& other) const { return {x - other.x, y - other.y}; }
		Vec2I operator=(const Vec2I& other) const { return { other.x, other.y };  }
	};

}