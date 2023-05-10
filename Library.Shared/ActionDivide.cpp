#include "ActionDivide.h"
using namespace std;
using namespace std::string_literals;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionDivide);
	ActionDivide::ActionDivide() :
		Action(TypeIdClass())
	{
	}

	void ActionDivide::Update(const GameTime& currentTime)
	{
		currentTime;
		Datum* targetDatum = Search(Target);
		if (targetDatum != nullptr && targetDatum->Type() == Datum::DatumTypes::Integer && targetDatum->Size() >= Index && Divisor != 0)
		{
			targetDatum->SetInt(targetDatum->GetInt(Index) / Divisor, Index);
		}
	}

	Vector<Signature> ActionDivide::Signatures()
	{
		Vector<Signature> signatureArray = Action::Signatures();
		signatureArray.PushBack(Signature{ "Target", Datum::DatumTypes::String, 1, offsetof(ActionDivide, Target) });
		signatureArray.PushBack(Signature{ "Divisor", Datum::DatumTypes::Integer, 1, offsetof(ActionDivide, Divisor) });
		signatureArray.PushBack(Signature{ "Index", Datum::DatumTypes::Integer, 1, offsetof(ActionDivide, Index) });
		return signatureArray;
	}
}