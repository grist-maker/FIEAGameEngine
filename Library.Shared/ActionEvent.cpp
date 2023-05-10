#include "ActionEvent.h"
#include "pch.h"

using namespace std;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionEvent);
	ActionEvent::ActionEvent():
		Action(TypeIdClass())
	{
	}

	void ActionEvent::Update(const GameTime& currentTime)
	{
		EventMessageAttributed newEvent(Subtype);
		CopyAuxiliaryAttributes(newEvent);
		std::shared_ptr<EventPublisher> newEventPublisher(new Event<EventMessageAttributed>(newEvent));
		GameState::Queue.Enqueue(newEventPublisher, currentTime.CurrentTime(), std::chrono::milliseconds(Delay));
	}

	void ActionEvent::CopyAuxiliaryAttributes(EventMessageAttributed& newEvent) const
	{
		auto auxRange = GetAuxiliaryAttributes();
		for (size_t i = auxRange.first; i < auxRange.second; i++)
		{
			auto keypair = GetPair(i);
			auto& currentAttribute = newEvent.AppendAuxiliaryAttribute(keypair.first);
			currentAttribute = keypair.second;
		}
	}

	Vector<Signature> ActionEvent::Signatures()
	{
		Vector<Signature> signatureArray = Action::Signatures();
		signatureArray.PushBack(Signature{ "Subtype", Datum::DatumTypes::String, 1, offsetof(ActionEvent, Subtype) });
		signatureArray.PushBack(Signature{ "Delay", Datum::DatumTypes::Integer, 1, offsetof(ActionEvent, Delay) });
		return signatureArray;
	}
}