#pragma once
#include "RTTI.h"
#include "Vector.h"
#include "EventSubscriber.h"
#include "GameState.h"

namespace FieaGameEngine
{
	class EventPublisher: public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI);
	protected:
		/// <summary>
		/// The only constructor for the EventPublisher class, taking a single argument with no default value. It takes in a Vector by reference,
		///  populated with raw pointers containing each subscriber to the event type that is currently invoking the EventPublisher base
		/// constructor. This allows the Event to contain a static vector of subscribers, while also sending a non-static reference to the
		/// EventPublisher so it may traverse it for its Notify call.
		/// </summary>
		/// <param name="subscribers">A reference to the EventSubscriber vector, allowing it to stay informed of what
		/// entities are currently listening for updates in the Event.</param>
		EventPublisher(Vector<EventSubscriber*>& subscribers);

	public:
		/// <summary>
		/// The copy constructor for the EventPublisher class. This creates a deep copy of the EventPublisher argument provided inside
		/// of the calling EventPublisher, effectively setting all values in the calling EventPublisher to make it functionally equal to the argument.
		/// No special work that has not already been provided is necessary, so operation is defaulted.
		/// </summary>
		/// <param name="copiedPublisher">The EventPublisher being copied into the calling EventPublisher.</param>
		EventPublisher(EventPublisher& copiedPublisher) = default;
		/// <summary>
		/// The move constructor for the EventPublisher class. This creates a shallow copy of the EventPublisher argument provided inside
		/// of the calling EventPublisher, effectively moving its memory directly into the calling EventPublisher. No special work that has not
		/// already been provided is necessary, so operation is defaulted.
		/// </summary>
		/// <param name="movedPublisher">The EventPublisher being moved into the calling EventPublisher.</param>
		EventPublisher(EventPublisher&& movedPublisher)= default;

		/// <summary>
		/// The copy assignment operator for the EventPublisher class. This creates a deep copy of the EventPublisher argument provided inside
		/// of the calling EventPublisher, effectively setting all values in the calling EventPublisher to make it functionally equal to the argument.
		/// No special work that has not already been provided is necessary, so operation is defaulted.
		/// </summary>
		/// <param name="copiedPublisher">The EventPublisher being copied into the calling EventPublisher.</param>
		/// <returns>A reference to the EventPublisher now containing the same data values as the argument provided.</returns>
		EventPublisher& operator=(EventPublisher& copiedPublisher) = default;
		/// <summary>
		/// The move assignment operator for the EventPublisher class. This creates a shallow copy of the EventPublisher argument provided inside
		/// of the calling EventPublisher, effectively moving its memory directly into the calling EventPublisher. No special work that has not
		/// already been provided is necessary, so operation is defaulted.
		/// </summary>
		/// <param name="movedPublisher">The EventPublisher being moved into the calling EventPublisher.</param>
		/// <returns>A reference to the EventPublisher now containing the same memory as the argument provided.</returns>
		EventPublisher& operator=(EventPublisher&& movedPublisher) = default;

		/// <summary>
		/// The pure virtual deliver method for the EventPublisher. This is a mechanism of allowing code reuse and avoiding code bloat in derived Event classes, by providing
		/// a simple mechanism for notifications to be sent out to each subscriber.
		/// </summary>
		virtual void Deliver() const = 0;
		/// <summary>
		/// The virtual destructor for the EventPublisher class. No special work needs to be done, so it is defaulted.
		/// </summary>
		virtual ~EventPublisher() = default;

	protected:
		/// <summary>
		/// A pointer to a vector containing pointers to EventSubscribers. This allows the EventPublisher to access the contents of the static Subscriber vector in each
		/// Event derived class instance nonstatically, while still allowing it the subscriber list it needs to deliver messages for each given event.
		/// </summary>
		Vector<EventSubscriber*>* EventSubscribers;
	};
}