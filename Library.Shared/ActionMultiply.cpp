#include "ActionMultiply.h"
using namespace std;
using namespace std::string_literals;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionMultiply);

	ActionMultiply::ActionMultiply() :
		Action(TypeIdClass())
	{
	}

	void ActionMultiply::Update(const GameTime& currentTime)
	{
		currentTime;
		Datum* targetDatum = Search(Target);
		if (targetDatum != nullptr && targetDatum->Type() == Datum::DatumTypes::Integer && targetDatum->Size() >= Index)
		{
			targetDatum->SetInt(targetDatum->GetInt(Index) * Multiplier, Index);
		}
	}

	Vector<Signature> ActionMultiply::Signatures()
	{
		Vector<Signature> signatureArray = Action::Signatures();
		signatureArray.PushBack(Signature{ "Target", Datum::DatumTypes::String, 1, offsetof(ActionMultiply, Target) });
		signatureArray.PushBack(Signature{ "Multiplier", Datum::DatumTypes::Integer, 1, offsetof(ActionMultiply, Multiplier) });
		signatureArray.PushBack(Signature{ "Index", Datum::DatumTypes::Integer, 1, offsetof(ActionMultiply, Index) });
		return signatureArray;
	}
}