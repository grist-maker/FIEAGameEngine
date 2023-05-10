#pragma once
#include <chrono>
namespace FieaGameEngine
{
	/// <summary>
/// The GameTime class is used by the GameClock class to update time and its passing within a game. It can be manually set to log start time, total time, and elapsed time within a game. This can
/// then be passed as input to a clock to influence behaviors and reactions of GameObjects.
/// </summary>
	class GameTime final
	{
	public:
		/// <summary>
		/// Retrieves and returns the current time in milliseconds recorded by the GameTime instance.
		/// </summary>
		/// <returns>The current time in milliseconds recorded by the GameTime instance.</returns>
		[[nodiscard]] const std::chrono::high_resolution_clock::time_point& CurrentTime() const;
		/// <summary>
		/// Allows the user to set the current time to be recorded by the calling GameTime instance.
		/// </summary>
		/// <param name="currentTime">The desired time in millisecond to be recorded by the GameTime instance.</param>
		void SetCurrentTime(const std::chrono::high_resolution_clock::time_point& currentTime);

		/// <summary>
		/// Returns the total passed time in milliseconds as recorded by the GameTime instance.
		/// </summary>
		/// <returns>The passed time in milliseconds as recorded by the GameTime instance.</returns>
		[[nodiscard]] const std::chrono::milliseconds& TotalGameTime() const;
		/// <summary>
		/// Allows the user to set the total time (total passed time recorded by the GameTime instance) in milliseconds.
		/// </summary>
		/// <param name="totalGameTime">The total time in milliseconds that should now be recorded by the calling GameTime instance.</param>
		void SetTotalGameTime(const std::chrono::milliseconds& totalGameTime);

		/// <summary>
		/// Retreives and returns the elapsed game time (difference between the last two time updates) in milliseconds.
		/// </summary>
		/// <returns>The elapsed game time in milliseconds.</returns>
		[[nodiscard]] const std::chrono::milliseconds& ElapsedGameTime() const;
		/// <summary>
		/// Allows the user to set the elapsed game time (difference between last two time updates) in milliseconds.
		/// </summary>
		/// <param name="elapsedGameTime">The desired elapsed game time to be carried by the calling GameTime instance.</param>
		void SetElapsedGameTime(const std::chrono::milliseconds& elapsedGameTime);

		/// <summary>
		/// Returns the total game time (time passed over the course of the GameTime instance's operation) in seconds.
		/// </summary>
		/// <returns>The passed time in seconds as recorded by the GameTime instance.</returns>
		[[nodiscard]] std::chrono::duration<float> TotalGameTimeSeconds() const;
		/// <summary>
		/// Returns the elapsed game time (difference between last two time updates) in seconds.
		/// </summary>
		/// <returns>The elapsed game time in seconds as recorded by the GameTime instance.</returns>
		[[nodiscard]] std::chrono::duration<float> ElapsedGameTimeSeconds() const;

	private:
		/// <summary>
		/// Logs the current time recorded by the GameTime instance.
		/// </summary>
		std::chrono::high_resolution_clock::time_point MillisecondCurrentTime;
		/// <summary>
		/// Logs the number of milliseconds that have passed over the course of the GameTime instance's operation.
		/// </summary>
		std::chrono::milliseconds MillisecondTotalGameTime{ 0 };
		/// <summary>
		/// Logs the number of milliseconds that have passed between the last two updates to the GameTime instance, the difference between current and total game time.
		/// </summary>
		std::chrono::milliseconds MillisecondElapsedGameTime{ 0 };
	};
}