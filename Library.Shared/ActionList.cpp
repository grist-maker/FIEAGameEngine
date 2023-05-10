#include "ActionList.h"
#include "pch.h"
using namespace std;
using namespace std::string_literals;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionList);
	ActionList::ActionList() :
		Action(TypeIdClass())
	{
	}
	ActionList::ActionList(size_t typeId) :
		Action(typeId)
	{
	}
	Vector<Signature> ActionList::Signatures()
	{
		Vector<Signature> signatureArray;
		signatureArray = Action::Signatures();
		signatureArray.PushBack(Signature{ "Actions", Datum::DatumTypes::Table, 1, 0 });
		return signatureArray;
	}

	void ActionList::Update(const GameTime& currentTime)
	{
		UpdateNestedActions(Find("Actions"), currentTime);
	}
}