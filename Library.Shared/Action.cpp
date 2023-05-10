#include "pch.h"
#include "Action.h"
#include "Reaction.h"

using namespace std;
using namespace std::string_literals;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Action);
	Action::Action() :
		Attributed(TypeIdClass())
	{
	}

	Action::Action(const size_t typeId) :
		Attributed(typeId)
	{
	}

	void Action::SetName(const std::string& newName)
	{
		Name = newName;
	}

	void Action::Update(const GameTime& currentTime)
	{
		currentTime;
	}

	const std::string& Action::GetName() const
	{
		return Name;
	}

	Vector<Signature> Action::Signatures()
	{
		Vector<Signature> signatureArray;
		signatureArray.PushBack(Signature{ "Name", Datum::DatumTypes::String, 1, offsetof(Action, Name) });
		return signatureArray;
	}

	void Action::UpdateNestedActions(Datum* targetDatum, const GameTime& currentTime)
	{
		if (targetDatum != nullptr)
		{
			for (size_t i = 0; i < targetDatum->Size(); i++)
			{
				auto& currentContainer = (*targetDatum)[i];
				for (size_t j = 0; j < currentContainer.Size(); j++)
				{
					auto nestedAction = currentContainer.At(j).GetScope();
					assert(nestedAction->Is(Action::TypeIdClass()));
					static_cast<Action*>(nestedAction)->Update(currentTime);
				}
			}
		}
	}
}