#include "ActionListWhile.h"
#include "pch.h"
using namespace std;
using namespace std::string_literals;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionListWhile);
	ActionListWhile::ActionListWhile() :
		Action(TypeIdClass())
	{}

	Vector<Signature> ActionListWhile::Signatures()
	{
		Vector<Signature> signatureArray;
		signatureArray = Action::Signatures();
		signatureArray.PushBack(Signature{ "Condition", Datum::DatumTypes::Integer, 1, offsetof(ActionListWhile, Condition) });
		signatureArray.PushBack(Signature{ "Preamble", Datum::DatumTypes::Table, 1, 0 });
		signatureArray.PushBack(Signature{ "Increment", Datum::DatumTypes::Table, 1, 0 });
		signatureArray.PushBack(Signature{ "LoopAction", Datum::DatumTypes::Table, 1, 0 });
		return signatureArray;
	}

	void ActionListWhile::Update(const GameTime& currentTime)
	{
		auto loop = Find("LoopAction");
		auto increment = Find("Increment");

		UpdateNestedActions(Find("Preamble"), currentTime);
		while (Condition)
		{
			UpdateNestedActions(loop, currentTime);
			UpdateNestedActions(increment, currentTime);
		}
	}
}