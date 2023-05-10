#include "ReactionAttributed.h"
#include "pch.h"

using namespace std;
using namespace std::string_literals;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionAttributed);

	ReactionAttributed::ReactionAttributed():
		Reaction(TypeIdClass())
	{
		Event<EventMessageAttributed>::Subscribe(this);
	}

	ReactionAttributed::ReactionAttributed(const size_t typeId) :
		Reaction(typeId)
	{
		Event<EventMessageAttributed>::Subscribe(this);
	}

	void ReactionAttributed::Notify(const EventPublisher* eventPublisher)
	{
		assert(eventPublisher->Is(Event<EventMessageAttributed>::TypeIdClass()));
		auto publisher = static_cast<const Event<EventMessageAttributed>*>(eventPublisher)->Message();
		for (size_t i = 0; i < Subtype->size(); i++)
		{
			if (publisher.GetSubtype() == Subtype[i])
			{
				CopyAuxiliaryAttributes(publisher);
				Reaction::Notify(eventPublisher);
				break;
			}
		}
	}


	void ReactionAttributed::CopyAuxiliaryAttributes(const EventMessageAttributed& publisher)
	{
		auto publisherIndices = publisher.GetAuxiliaryAttributes();

		for (size_t j = publisherIndices.first; j < publisherIndices.second; j++)
		{
			auto keyPair = publisher.GetPair(j);
			if (!IsPrescribedAttribute(keyPair.first))
			{
				auto& newAttribute = AppendAuxiliaryAttribute(keyPair.first);
				newAttribute = keyPair.second;
			}
			else //If it is a prescribed attribute, we don't do the append. We just set the value, as long as they are the same datum type.
			{
				auto& prescribedAttribute = *Find(keyPair.first);
				if (prescribedAttribute.Type() == keyPair.second.Type())
				{
					prescribedAttribute = keyPair.second;
				}
			}
		}
	}

	void ReactionAttributed::Update(const GameTime& currentTime)
	{
		ActionList::Update(currentTime);
	}
	
	ReactionAttributed::~ReactionAttributed()
	{
		Event<EventMessageAttributed>::Unsubscribe(this);
	}

	Vector<Signature> ReactionAttributed::Signatures()
	{
		Vector<Signature> signatureArray = Reaction::Signatures();
		signatureArray.PushBack(Signature{ "Subtype", Datum::DatumTypes::String, 3, offsetof(ReactionAttributed, Subtype) });
		return signatureArray;
	}
}