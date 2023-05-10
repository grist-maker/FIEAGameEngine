#include "EventPublisher.h"
#include "pch.h"
#include <future>

using namespace std;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventPublisher);

	EventPublisher::EventPublisher(Vector<EventSubscriber*>& subscribers):
		EventSubscribers(&subscribers)
	{
	}

	void EventPublisher::Deliver() const
	{
		if (EventSubscribers != nullptr)
		{
			for (size_t i = 0; i < EventSubscribers->Size(); i++)
			{
				if ((*EventSubscribers)[i] != nullptr)
				{
					(* EventSubscribers)[i]->Notify(this);
				}
			}
		}
	}
}