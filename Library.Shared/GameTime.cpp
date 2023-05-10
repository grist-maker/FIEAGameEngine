#include "GameTime.h"

using namespace std;
using namespace chrono;
namespace FieaGameEngine
{
	const high_resolution_clock::time_point& GameTime::CurrentTime() const
	{
		return MillisecondCurrentTime;
	}

	void GameTime::SetCurrentTime(const high_resolution_clock::time_point& currentTime)
	{
		MillisecondCurrentTime = currentTime;
	}

	const milliseconds& GameTime::TotalGameTime() const
	{
		return MillisecondTotalGameTime;
	}

	void GameTime::SetTotalGameTime(const milliseconds& totalGameTime)
	{
		MillisecondTotalGameTime = totalGameTime;
	}

	const milliseconds& GameTime::ElapsedGameTime() const
	{
		return MillisecondElapsedGameTime;
	}

	void GameTime::SetElapsedGameTime(const milliseconds& elapsedGameTime)
	{
		MillisecondElapsedGameTime = elapsedGameTime;
	}

	duration<float> GameTime::TotalGameTimeSeconds() const
	{
		return duration_cast<duration<float>>(MillisecondTotalGameTime);
	}

	duration<float> GameTime::ElapsedGameTimeSeconds() const
	{
		return duration_cast<duration<float>>(MillisecondElapsedGameTime);
	}
}