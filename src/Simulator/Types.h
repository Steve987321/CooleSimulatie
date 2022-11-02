#pragma once

namespace sim
{

	struct Vec2
	{
		int x, y;
		Vec2() : x(0), y(0) {}
		Vec2(int X, int Y) : x(X), y(Y) {}

		bool operator==(const Vec2& other) { return x == other.x && y == other.y; }

		Vec2& operator+(const Vec2& other) { x += other.x; y += other.y; }
		Vec2& operator-(const Vec2& other) { x -= other.x; y -= other.y; }
		Vec2& operator=(const Vec2& other) { x = other.x; y = other.y; }
	};

}