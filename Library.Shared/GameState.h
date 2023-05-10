#pragma once
#include <memory>
#include "GameClock.h"
#include "EventQueue.h"

namespace FieaGameEngine
{
	/// <summary>
	/// A struct that is composed of several static members, each necessary for proper execution of events and updates based on time in a running game. This allows easy public access
	/// to important data within the game.
	/// </summary>
	struct GameState
	{
	public:
		inline static GameClock Clock;
		inline static GameTime CurrentTime;
		inline static EventQueue Queue;
	};
}