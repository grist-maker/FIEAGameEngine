#include "EventQueue.h"
#include "EventPublisher.h"

using namespace std;
using namespace chrono;

namespace FieaGameEngine
{
	void EventQueue::Enqueue(const std::shared_ptr<EventPublisher> newEvent, high_resolution_clock::time_point startTime, milliseconds delay)
	{
		std::shared_ptr<QueueEntry> newEntry(new QueueEntry);
		newEntry.get()->StoredEvent = newEvent;
		newEntry.get()->ExpirationTime = startTime + delay;

		if (Events.Find(*newEntry.get()) == Events.end() && CreateQueue.Find(*newEntry.get()) == CreateQueue.end())
		{
			CreateQueue.PushBack(*newEntry.get());
		}
	}

	void EventQueue::Dequeue(const EventPublisher* removedEvent)
	{
		for (size_t i = 0; i < Events.Size(); i++)
		{
			if (Events[i].StoredEvent.get() == removedEvent) //Events need to be present in the Events queue to be removed
			{
				if (DeleteQueue.Find(Events[i]) == DeleteQueue.end())
				{
					DeleteQueue.PushBack(Events[i]);
				}
			}
		}
	}

	void EventQueue::Clear()
	{
		DeleteQueue = Events;
		CreateQueue.Clear();
	}

	bool EventQueue::IsEmpty() const
	{
		return Events.IsEmpty();
	}
	size_t EventQueue::Size() const
	{
		return Events.Size();
	}

	void EventQueue::Update(const GameTime& currentTime)
	{
		if(!IsUpdating)
		{
			IsUpdating = true;
			Vector<QueueEntry>::Iterator newIterator = std::partition(Events.begin(), Events.end(), [this, currentTime](QueueEntry currentEntry)
			{
				return IsExpired(currentEntry, currentTime);
			});
			for (auto firstPartition = Events.begin(); firstPartition != newIterator; firstPartition++)
			{
				((*firstPartition).StoredEvent->Deliver());
			}
			if (newIterator != Events.begin())
			{
				Events.Remove(Events.begin(), newIterator - 1);
			}
			for (size_t i = 0; i < CreateQueue.Size(); i++)
			{
				Events.PushBack(CreateQueue[i]);
			}
			for (size_t i = 0; i < DeleteQueue.Size(); i++)
			{
				Events.Remove(DeleteQueue[i]);
			}
			DeleteQueue.Clear();
			CreateQueue.Clear();
			IsUpdating = false;
		}
	}

	bool EventQueue::IsExpired(const QueueEntry& currentEvent, const GameTime& currentTime) const
	{
		return(currentEvent.ExpirationTime <= currentTime.CurrentTime());
	}

	bool EventQueue::QueueEntry::operator==(const QueueEntry& comparedEntry) const
	{
		return(StoredEvent == comparedEntry.StoredEvent);
	}

	void EventQueue::TestClear()
	{
		CreateQueue.~Vector();
		DeleteQueue.~Vector();
		Events.~Vector();
	}
}