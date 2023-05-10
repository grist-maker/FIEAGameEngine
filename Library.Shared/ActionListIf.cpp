#include "ActionListIf.h"
#include "pch.h"
using namespace std;
using namespace std::string_literals;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionListIf);
	ActionListIf::ActionListIf() :
		Action(TypeIdClass())
	{}

	Vector<Signature> ActionListIf::Signatures()
	{
		Vector<Signature> signatureArray;
		signatureArray = Action::Signatures();
		signatureArray.PushBack(Signature{"Condition", Datum::DatumTypes::Integer, 1, offsetof(ActionListIf, Condition) });
		signatureArray.PushBack(Signature{ "TrueBlock", Datum::DatumTypes::Table, 1, 0 });
		signatureArray.PushBack(Signature{ "FalseBlock", Datum::DatumTypes::Table, 1, 0 });
		return signatureArray;
	}

	void ActionListIf::Update(const GameTime& currentTime)
	{
		Action::Update(currentTime);
		Datum* actionDatum;
		if (Condition)
		{
			actionDatum = Find("TrueBlock"s);
		}
		else
		{
			actionDatum = Find("FalseBlock"s);
		}
		UpdateNestedActions(actionDatum, currentTime);
	}
}