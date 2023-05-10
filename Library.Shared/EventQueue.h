#pragma once
#include "GameTime.h"
#include "Vector.h"
#include <atomic>
#include <algorithm>
#include <thread>
#include <mutex>
#include <future>

namespace FieaGameEngine
{
	class EventPublisher;
	/// <summary>
	/// The EventQueue class is used to manage event firing and addition within the game, meaning events don't need to manage themselves. Instead, the queue directs event deliver, subscriber
	/// notification, and subsequent removal of called events from the queue on their completion.
	/// </summary>
	class EventQueue final
	{
	private:
		/// <summary>
		/// The Queue Entry struct is used to combine an event shared pointer and the time at which this event will expire into a single structure, allowing it to be used to compose vectors
		/// for the queue.
		/// </summary>
		struct QueueEntry
		{
			/// <summary>
			/// A shared pointer to the event inside of the Queue Entry.
			/// </summary>
			std::shared_ptr<EventPublisher> StoredEvent;
			/// <summary>
			/// The point in time (in milliseconds) that the event will expire. At this point, the event will fire and be removed from the Events Vector.
			/// </summary>
			std::chrono::high_resolution_clock::time_point ExpirationTime;
			/// <summary>
			/// The == operator overload for QueueEntry, which allows two QueueEntry objects to be logically compared. Returns a boolean indicating whether or not the caller and the
			/// argument comparedEntry are equivalent.
			/// </summary>
			/// <param name="comparedEntry">A const reference to a QueueEntry which is being logically compared to the calling QueueEntry.</param>
			/// <returns>A boolean indicating whether or not the QueueEntry objects are equivalent.</returns>
			bool operator==(const QueueEntry& comparedEntry) const;
		};
		/// <summary>
		/// A boolean indicating whether or not the EventQueue is currently updating. This prevents recursive update calls, in the event that a subscriber attempts an Event Queue Update
		/// call in response to message delivery.
		/// </summary>
		std::atomic<bool> IsUpdating = false;
		/// <summary>
		/// The queue of current events. These are cycled through on update to see if they expire and trigger notifications to subscribers.
		/// </summary>
		Vector<QueueEntry> Events;
		/// <summary>
		/// A Vector of Queue Entries, acting as a queue holding those entries that are pending enqueue into the Events queue. This ensures that no vector mutation is performed on Events while
		/// it is being traversed, as in the Update loop.
		/// </summary>
		Vector<QueueEntry> CreateQueue;
		/// <summary>
		/// A Vector of Queue Entries, acting as a queue holding those entries that are pending removal from the Events queue. This ensures that no vector mutation is performed on Events while
		/// it is being traversed, as in the Update loop.
		/// </summary>
		Vector<QueueEntry> DeleteQueue;
	public:
		EventQueue() = default;
		/// <summary>
		/// Adds a new Event into the Event Queue, also recording whether it should be deleted after firing, its enqueue time, and the delay before it should be sent. This will allow
		/// it to be sent at the time specified automatically, with the Event not needing to manage itself.
		/// </summary>
		/// <param name="newEvent">A shared pointer to an event publisher, containing the new Event to be enqueued.</param>
		/// <param name="startTime">The time point at which the event was enqueued.</param>
		/// <param name="delay">The delay (in milliseconds) that should pass after event enqueue time before the event is fired.</param>
		void Enqueue(const std::shared_ptr<EventPublisher> newEvent, std::chrono::high_resolution_clock::time_point startTime, std::chrono::milliseconds delay = std::chrono::milliseconds{ 0 });
		/// <summary>
		/// The dequeue method allows a user to remove an event from the event queue, provided a pointer to the same event.
		/// </summary>
		/// <param name="removedEvent">A const, raw pointer to the event to be removed. This is not required to be a shared pointer to allow subscribers to more easily call it
		/// if necessary, as long as they know the address of the event they wish to dequeue.</param>
		void Dequeue(const EventPublisher* removedEvent);

		/// <summary>
		/// Clears the current Event Queue, provided an update is not currently taking place. This means that all events are removed from the queue, and are no longer being updated by the queue.
		/// </summary>
		void Clear();
		/// <summary>
		/// Checks to see if any events are present inside of the calling Event Queue, that is, whether or not it contains any events. If so, returns false. Otherwise, returns true.
		/// </summary>
		/// <returns>A boolean indicating whether or not the Event Queue is empty (has no events inside of the queue).</returns>
		bool IsEmpty() const;
		/// <summary>
		/// Checks the Event Queue to see how many events are currently managed by it, returning the number of events that it manages as a size_t.
		/// </summary>
		/// <returns>A size_t indicating the number of elements within the queue.</returns>
		size_t Size() const;

		/// <summary>
		/// The update method for the EventQueue class cycles through all of the events it's holding in its Events vector, checking to see if they have expired and should notify all subscribers.
		/// This is also where enqueue calls and dequeue calls that are sitting in the Create and Destroy Vectors are carried over to the Events Vector, upon completion of the check for expired
		/// events.
		/// </summary>
		/// <param name="currentTime">The current game time, used to determine expiration of events.</param>
		void Update(const GameTime& currentTime);

		/// <summary>
		/// Checks whether or not the QueueEntry provided is expired based on the input current game time. Returns a boolean variable indicating the result.
		/// </summary>
		/// <param name="currentEvent">A const reference to the QueueEntry being checked for expiration.</param>
		/// <param name="currentTime">The current time within the game, passed as a const GameTime reference that cannot be mutated.</param>
		bool IsExpired(const QueueEntry& currentPublisher, const GameTime& currentTime) const;

		void TestClear();
	};
}