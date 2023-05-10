#pragma once
namespace FieaGameEngine
{
	class EventPublisher;
	/// <summary>
	/// The abstract base class that provides a base for any derived subscribers to inherit from. It contains a function, Notify, that should be overriden to provide special behavior for each subscriber. This
	/// lets EventPublishers and Events deal simply with the EventSubscriber class instead of all those classes that can inherit from EventSubscriber.
	/// </summary>
	class EventSubscriber
	{
	public:
		/// <summary>
		/// The Notify function, used to alert an individual subscriber that the Event they're interested in has new information to share.
		/// </summary>
		/// <param name="eventPublisher">A constant pointer to the Publisher that contains the Event with new information to relay to subscribers.</param>
		virtual void Notify(const EventPublisher* eventPublisher) = 0;
		/// <summary>
		/// The virtual destructor for the EventSubscriber class. No special operation is needed, so it may be defaulted.
		/// </summary>
		virtual ~EventSubscriber() = default;
	};
}