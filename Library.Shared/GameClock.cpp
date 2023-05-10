#include "GameClock.h"
using namespace std;
using namespace chrono;

namespace FieaGameEngine
{
	GameClock::GameClock()
	{
		Reset();
	}
	const high_resolution_clock::time_point& GameClock::StartTime() const
	{
		return StartTimeStamp;
	}

	const high_resolution_clock::time_point& GameClock::CurrentTime() const
	{
		return CurrentTimeStamp;
	}
	const high_resolution_clock::time_point& GameClock::LastTime() const
	{
		return LastTimeStamp;
	}

	void GameClock::Reset()
	{
		StartTimeStamp = high_resolution_clock::now();
		CurrentTimeStamp = StartTimeStamp;
		LastTimeStamp = CurrentTimeStamp;
	}
	void GameClock::UpdateGameTime(GameTime& gameTime)
	{
		CurrentTimeStamp = high_resolution_clock::now();

		gameTime.SetCurrentTime(CurrentTimeStamp);
		gameTime.SetTotalGameTime(duration_cast<milliseconds>(CurrentTimeStamp - StartTimeStamp));
		gameTime.SetElapsedGameTime(duration_cast<milliseconds>(CurrentTimeStamp - LastTimeStamp));

		LastTimeStamp = CurrentTimeStamp;
	}
}