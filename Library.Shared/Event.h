#pragma once
#include "EventPublisher.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Used to generate events of a type specified by the user (T) which can send information on changes in this type value to entities that subscribe
	/// to events of its type. Acts as a wrapper to the message T, and transmits the data inside it to subscribers without allowing modification,
	/// otherwise allowing them to act on the information as specified in their Notify functions.
	/// </summary>
	template <typename T>
	class Event final : public EventPublisher
	{
		RTTI_DECLARATIONS(Event, EventPublisher);

	public:
		Event() = delete;
		/// <summary>
		/// The constructor for the Event class, taking in one argument: a copy of the message (T) object. This T is intended for consumption by the Event holding it, and should not be considered
		/// a reference.
		/// </summary>
		/// <param name="message">The templated T, this T object being a message that the Event will carry to be published.</param>
		explicit Event(T message);

		/// <summary>
		/// The copy constructor for the Event class, deep-copying the Event argument into the newly constructed Event. This means both the argument
		/// and the constructed Event will have functionally equal data, but be separate event objects, each of which can be modified without
		/// adjusting the other.
		/// </summary>
		/// <param name="copiedEvent">The Event being deep-copied into the newly constructed Event.</param>
		Event(Event& copiedEvent) = default;
		/// <summary>
		/// The move constructor for the Event class. This creates a shallow copy of the Event argument provided inside of the newly constructed
		/// Event, effectively moving its memory directly into the calling Event. This makes the argument provided unusable post assignment.
		/// </summary>
		/// <param name="movedEvent">The Event being moved into the newly constructed Event.</param>
		Event(Event&& movedEvent) =default;

		/// <summary>
		/// The copy assignment operator for the Event class, deep-copying the Event argument into the calling Event. This means both the argument
		/// and the calling Event will have functionally equal data, but be separate event objects, each of which can be modified without
		/// adjusting the other.
		/// </summary>
		/// <param name="copiedEvent">The Event being deep-copied into the calling Event.</param>
		/// <returns>A reference to the Event that has now been populated with copies of the argument Event's data.</returns>
		Event& operator=(Event& copiedEvent) = default;
		/// <summary>
		/// The move assignment operator for the Event class. This creates a shallow copy of the Event argument provided inside of the calling
		/// Event, effectively moving its memory directly into the calling Event. This makes the argument provided unusable post assignment.
		/// </summary>
		/// <param name="movedEvent">The Event being moved into the calling Event.</param>
		/// <returns>A reference to the Event now containing the same memory as the argument provided.</returns>
		Event& operator=(Event&& movedEvent)= default;

		/// <summary>
		/// The defaulted virtual destructor for the Event class. No special work needs to be done, so it does not need to be explicitly defined.
		/// </summary>
		virtual ~Event() = default;

		/// <summary>
		/// Adds a new EventSubscriber to the subscriber list for this event, if it is not already present. This will allow it to receive
		/// updates when the Event receives new messages or its state changes.
		/// </summary>
		/// <param name="newSubscriber">A pointer to the event subscriber that is joining the list of subscribers for this event.
		/// Now, it will receive all of this event's updates automatically.</param>
		static void Subscribe(EventSubscriber* newSubscriber);
		/// <summary>
		/// Removes a single target event subscriber from the list of subscribers for this event, meaning it will no longer receive this
		/// event's updates.
		/// </summary>
		/// <param name="oldSubscriber">A pointer to the EventSubscriber that will no longer receive updates from this Event.</param>
		static void Unsubscribe(EventSubscriber* newSubscriber);
		/// <summary>
		/// Unsubscribes all current subscribers from this event type, meaning no EventSubscribers will receive this event's updates
		/// anymore.
		/// </summary>
		static void UnsubscribeAll();
		
		/// <summary>
		/// Returns the message associated with this Event, an object of type T that it holds.
		/// </summary>
		/// <returns>A const reference to the T (message) that this event holds.</returns>
		const T& Message() const;
		/// <summary>
		/// The deliver method searches through the Vector EventSubscribersStatic to get all current subscribers, notifying each one that a new update has occurred. The
		/// override in this case simply invokes the base-class, EventPublisher Deliver method. The calling EventPublisher sends its own address as the single argument
		/// to notify to supply each subscriber with the new message, or data, it stores.
		/// </summary>
		virtual void Deliver() const override;

		/// <summary>
		/// A test method that simply invokes the destructors on EventSubscribersStatic, CreateQueue, and DestroyQueue to guard against memory leak notifications during
		/// testing, due to the fact that the static vectors are meant to persist for the duration of all unit tests, and thus mistakenly cause tests to return failure
		/// due to suspected memory leak.
		/// </summary>
		static void TestClear();
	private:
		/// <summary>
		/// The T object, or message, that the Event wrapper encapsulates for delivery to subscribers.
		/// </summary>
		T StoredMessage;
		/// <summary>
		/// The list of current subscribers to the event. This is composed of shared pointers to the subscribers themselves, and the list is iterated through on each
		/// notify event.
		/// </summary>
		inline static Vector<EventSubscriber*> EventSubscribersStatic;
		/// <summary>
		/// The list of pending subscribers to the event. These subscribers will be added before the next notification loop, so as to avoid mutation of the subscriber
		/// vector as it is iterated through.
		/// </summary>
		inline static Vector<EventSubscriber*> CreateQueue;
		/// <summary>
		/// The list of subscribers to be unsubscribed from the event. These subscribers will be removed before the next notification loop, so as to avoid mutation of the
		/// subscriber vector as it is iterated through.
		/// </summary>
		inline static Vector<EventSubscriber*> DeleteQueue;
	};
}
#include "Event.inl"