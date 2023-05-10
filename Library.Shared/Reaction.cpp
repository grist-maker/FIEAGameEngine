#include "pch.h"
#include "Reaction.h"

using namespace std;
using namespace std::string_literals;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Reaction);

	Reaction::Reaction() :
		ActionList(TypeIdClass())
	{
	}
	void Reaction::Notify(const EventPublisher*)
	{
		Update(GameState::CurrentTime);
	}

	Reaction::Reaction(const size_t typeId):
		ActionList(typeId)
	{
	}
}