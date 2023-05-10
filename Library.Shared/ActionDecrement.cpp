#include "ActionDecrement.h"
using namespace std;
using namespace std::string_literals;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionDecrement);
	ActionDecrement::ActionDecrement() :
		Action(TypeIdClass())
	{}

	void ActionDecrement::Update(const GameTime& currentTime)
	{
		currentTime;
		Datum* targetDatum = Search(Target);
		if (targetDatum != nullptr && targetDatum->Type() == Datum::DatumTypes::Integer)
		{
			if (Step > targetDatum->GetInt(Index))
			{
				targetDatum->SetInt(0, Index);
			}
			else
			{
				targetDatum->SetInt(targetDatum->GetInt(Index) - Step, Index);
			}
		}
	}

	Vector<Signature> ActionDecrement::Signatures()
	{
		Vector<Signature> signatureArray = Action::Signatures();
		signatureArray.PushBack(Signature{ "Target", Datum::DatumTypes::String, 1, offsetof(ActionDecrement, Target) });
		signatureArray.PushBack(Signature{ "Step", Datum::DatumTypes::Integer, 1, offsetof(ActionDecrement, Step) });
		signatureArray.PushBack(Signature{ "Index", Datum::DatumTypes::Integer, 1, offsetof(ActionDecrement, Index) });
		return signatureArray;
	}
}