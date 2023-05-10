#include "Event.h"
/// <summary>
/// The file specifying allowed operations and constructors for the Event class, outlining each potential method to be used on them.
/// </summary>
namespace FieaGameEngine
{
	template<typename T>
	RTTI_DEFINITIONS(Event<T>);

	template<typename T>
	Event<T>::Event(T message):
		StoredMessage(std::move(message)), EventPublisher::EventPublisher(EventSubscribersStatic)
	{
	}
	template<typename T>
	void Event<T>::TestClear()
	{
		EventSubscribersStatic.~Vector();
		CreateQueue.~Vector();
		DeleteQueue.~Vector();
	}

	template<typename T>
	void Event<T>::Subscribe(EventSubscriber* newSubscriber)
	{
		if (EventSubscribersStatic.Find(newSubscriber) == EventSubscribersStatic.end() && CreateQueue.Find(newSubscriber) == CreateQueue.end())
		{
			CreateQueue.PushBack(newSubscriber);
		}
	}

	template<typename T>
	void Event<T>::Unsubscribe(EventSubscriber* oldSubscriber)
	{
		if (EventSubscribersStatic.Find(oldSubscriber) != EventSubscribersStatic.end() && DeleteQueue.Find(oldSubscriber) == DeleteQueue.end())
		{
			DeleteQueue.PushBack(oldSubscriber);
		}
	}

	template<typename T>
	void Event<T>::UnsubscribeAll()
	{
		DeleteQueue = EventSubscribersStatic;
		CreateQueue.Clear();
	}

	template<typename T>
	const T& Event<T>::Message() const
	{
		return StoredMessage;
	}

	template<typename T>
	void Event<T>::Deliver() const
	{
		for (size_t i = 0; i < CreateQueue.Size(); i++)
		{
			EventSubscribersStatic.PushBack(CreateQueue[i]);
		}
		for (size_t i = 0; i < DeleteQueue.Size(); i++)
		{
			EventSubscribersStatic.Remove(DeleteQueue[i]);
		}
		DeleteQueue.Clear();
		CreateQueue.Clear();
		EventPublisher::Deliver();
	}
}