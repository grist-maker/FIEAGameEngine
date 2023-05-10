#include "ActionIncrement.h"
using namespace std;
using namespace std::string_literals;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionIncrement);

	ActionIncrement::ActionIncrement() :
		Action(TypeIdClass())
	{
	}

	void ActionIncrement::Update(const GameTime& currentTime)
	{
		currentTime;
		Datum* targetDatum = Search(Target);
		if (targetDatum != nullptr &&  targetDatum->Type() == Datum::DatumTypes::Integer && targetDatum->Size() >= Index)
		{
			targetDatum->SetInt(targetDatum->GetInt(Index) + Step, Index);
		}
	}

	Vector<Signature> ActionIncrement::Signatures()
	{
		Vector<Signature> signatureArray = Action::Signatures();
		signatureArray.PushBack(Signature{ "Target", Datum::DatumTypes::String, 1, offsetof(ActionIncrement, Target) });
		signatureArray.PushBack(Signature{ "Step", Datum::DatumTypes::Integer, 1, offsetof(ActionIncrement, Step)});
		signatureArray.PushBack(Signature{ "Index", Datum::DatumTypes::Integer, 1, offsetof(ActionIncrement, Index) });
		return signatureArray;
	}
}