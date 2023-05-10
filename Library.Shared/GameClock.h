#pragma once
#include "GameTime.h"

namespace FieaGameEngine
{
	class GameClock final
	{
	public:
		/// <summary>
		/// The default constructor for the GameClock. Resets the current, last, and starting timestamps by calling the reset function, initializing all values at 0 milliseconds.
		/// </summary>
		GameClock();
		/// <summary>
		/// The default copy constructor for the GameClock. No special behavior is necessary for the GameClock, so operation is defaulted.
		/// </summary>
		/// <param name="copiedClock">The clock having its data copied into the calling clock.</param>
		GameClock(const GameClock& copiedClock) = default;
		/// <summary>
			/// The default copy assignment operator for the GameClock. No special behavior is necessary for the GameClock, so operation is defaulted.
		/// </summary>
		/// <param name="copiedClock">The clock having its data copied into the calling clock.</param>	
		/// <returns></returns>
		GameClock& operator=(const GameClock& copiedClock) = default;
		/// <summary>
		/// The default move constructor for the GameClock. No special behavior is necessary for the GameClock, so operation is defaulted.
		/// </summary>
		/// <param name="rhsClock">The clock having its data moved into the calling clock.</param>
		GameClock(GameClock&& rhsClock) = default;
		/// <summary>
		/// The default move assignment operator for the GameClock. No special behavior is necessary for the GameClock, so operation is defaulted.
		/// </summary>
		/// <param name="rhsClock">The clock having its data moved into the calling clock.</param>
		/// <returns></returns>
		GameClock& operator=(GameClock&& rhsClock) = default;
		/// <summary>
		/// The default destructor for the GameClock. No special behavior is necessary for the GameClock, so operation is defaulted.
		/// </summary>
		~GameClock() = default;

		/// <summary>
		/// Returns the recorded point in time in milliseconds that the clock began ticking at.
		/// </summary>
		/// <returns>The timestamp in milliseconds that the clock started at.</returns>
		[[nodiscard]] const std::chrono::high_resolution_clock::time_point& StartTime() const;
		/// <summary>
		/// Returns the recorded point in time in milliseconds that the clock is currently at.
		/// </summary>
		/// <returns>The current ingame time recorded by the clock in milliseconds.</returns>
		[[nodiscard]] const std::chrono::high_resolution_clock::time_point& CurrentTime() const;
		/// <summary>
		/// Returns the recorded point in time in milliseconds that the clock was last updated at.
		/// </summary>
		/// <returns>The time at which the clock was last updated in milliseconds.</returns>
		[[nodiscard]] const std::chrono::high_resolution_clock::time_point& LastTime() const;

		/// <summary>
		/// Resets the GameClock, effectively reinitializing the current, start, and last times to 0.0 seconds, as they were upon game start. This completely discards all preexisting timestamp data.
		/// </summary>
		void Reset();
		/// <summary>
		/// Updates the current game time recorded in the passed in GameTime instance, setting it to whatever the high resolution clock logs the time as the current ingame time as reported by a high resolution
		/// clock. Similarly updates total game time, last time stamp, and elapsed game time to match new current time data.
		/// </summary>
		/// <param name="gameTime">The GameTime instance that's being updated by the clock based on current time data.</param>
		void UpdateGameTime(GameTime& gameTime);
		
	private:
		/// <summary>
		/// The timestamp recording the point at which the clock started in milliseconds.
		/// </summary>
		std::chrono::high_resolution_clock::time_point StartTimeStamp;
		/// <summary>
		/// The timestamp recording the point that the clock is currently at in milliseconds, the current ingame time.
		/// </summary>
		std::chrono::high_resolution_clock::time_point CurrentTimeStamp;
		/// <summary>
		/// The timestamp recording the millisecond point at which the clock was last updated.
		/// </summary>
		std::chrono::high_resolution_clock::time_point LastTimeStamp;
	};
}