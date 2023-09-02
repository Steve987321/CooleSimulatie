#pragma once

// base of game which every game script derives from

#include <EngineCore.h>

#ifdef GAME_IS_EXPORT
#define GAME_API __declspec(dllexport)
#else
#define GAME_API __declspec(dllimport)
#endif

class GAME_API GameBase
{
public:
	GameBase();
	~GameBase();

public:
	


};

