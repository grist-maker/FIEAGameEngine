#include "pch.h"
#include "GameObject.h"

using namespace std;
using namespace std::string_literals;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(GameObject);

	GameObject::GameObject():
		Attributed(TypeIdClass())
	{
	}

	GameObject::GameObject(size_t typeId) :
		Attributed(typeId)
	{
	}

	Vector<Signature> GameObject::Signatures()
	{
		Vector<Signature> signatureArray;
		signatureArray.PushBack(Signature{ "Name", Datum::DatumTypes::String, 1, offsetof(GameObject, Name) });
		signatureArray.PushBack(Signature{ "Position", Datum::DatumTypes::Vector, 1, offsetof(GameObject, Position) });
		signatureArray.PushBack(Signature{ "Rotation", Datum::DatumTypes::Vector, 1, offsetof(GameObject, Rotation) });
		signatureArray.PushBack(Signature{ "Scale", Datum::DatumTypes::Vector, 1, offsetof(GameObject, Scale) });
		signatureArray.PushBack(Signature{ "Children", Datum::DatumTypes::Table, 3, 0 });
		signatureArray.PushBack(Signature{ "Actions", Datum::DatumTypes::Table, 3, 0 });

		return signatureArray;
	}

	void GameObject::Update(const GameTime& currentTime)
	{
		auto childrenDatum = Find("Children"s);
		if (childrenDatum != nullptr)
		{
			for (size_t i = 0; i < childrenDatum->Size() && childrenDatum->GetScope(i) != nullptr; i++)
			{
				for (size_t j = 0; j < childrenDatum->GetScope(i)->Size(); j++)
				{
					auto nestedScope = childrenDatum->GetScope(i)->At(j).GetScope();
					assert(nestedScope->Is(GameObject::TypeIdClass()));
					static_cast<GameObject*>(nestedScope)->Update(currentTime);
				}
			}
		}

		auto actionDatum = Find("Actions"s);
		if (actionDatum != nullptr)
		{
			for (size_t i = 0; i < actionDatum->Size() && actionDatum->GetScope(i) != nullptr; i++)
			{
				auto& actionContainer = (*actionDatum)[i];
				for (size_t j = 0; j < actionContainer.Size(); j++)
				{
					auto nestedScope = actionContainer.At(j).GetScope();
					assert(nestedScope->Is(Action::TypeIdClass()));
					static_cast<Action*>(nestedScope)->Update(currentTime);
				}
			}
		}
	}

	Datum* GameObject::Actions() const
	{
		return Find("Actions");
	}

	void GameObject::CreateAction(const std::string& className, const std::string& instanceName)
	{
		auto actionsDatum = Find("Actions");
		if (actionsDatum != nullptr)
		{
			assert(actionsDatum->Type() == Datum::DatumTypes::Table);
			actionsDatum->GetScope()->Adopt(Factory<Scope>::Create(className), instanceName);
		}
	}
}