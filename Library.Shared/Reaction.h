#pragma once
#include "EventSubscriber.h"
#include "ActionList.h"
namespace FieaGameEngine
{
	/// <summary>
	/// The Reaction class is used to allow calls to Update behavior only when certain conditions are met, this condition being the retrieval of a subscribed event notify call,
	/// instead of occuring on tick. This is effectively functional behavior that is triggered by a change in condition instead of automatically on change in GameTime.
	/// </summary>
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList);
	protected:
		/// <summary>
		/// The overloaded constructor that accepts a typeId variable to create new classes derived from Reaction.
		/// </summary>
		/// <param name="typeId">The RTTI ID for the derived type being constructed.</param>
		explicit Reaction(const size_t typeId);
		/// <summary>
		/// The Update method overload for Reaction. It is marked as protected to prevent any calls to it on tick, or explicitly by the user. The Update should be triggered only in response to events that
		/// the reaction subscribes to, so it is called only in Notify.
		/// </summary>
		/// <param name="currentTime">The current in-game time.</param>
		virtual void Update(const GameTime& currentTime) override  = 0;
	public:
		/// <summary>
		/// Default constructor for the Reaction class. This creates a default, base object of the Reaction class, not any of its derivatives, and accepts no arguments, with
		/// no return.
		/// </summary>
		Reaction();
		/// <summary>
		/// The default copy constructor for the reaction class, copying the right-hand side action to create an entirely new action with functionally equal data. No special
		/// work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedReaction">The reaction object being copied into the newly-constructed one.</param>
		Reaction(const Reaction& copiedReaction) = default;
		/// <summary>
		/// The default move constructor for the reaction class, moving the right-hand side reaction's memory and data into the newly constructed reaction in a shallow copy. The
		/// newly constructed reaction is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedReaction">The reaction object being moved into the newly-constructed one.</param>
		Reaction(Reaction&& movedReaction) = default;
		/// <summary>
		/// The default copy assignment operator for the reaction class, deep copying the right-hand side reaction to populate the calling reaction with functionally equal data.
		/// No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedReaction">The reaction object being copied into the left-hand one.</param>
		/// <returns>The calling reaction, now functionally equal to the argument provided.</returns>
		Reaction& operator=(const Reaction& copiedReaction) = default;
		/// <summary>
		/// The default move assignment operator for the reaction class, moving the right-hand side action's memory and data into the calling reaction in a shallow copy. The
		/// left-hand reaction is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedReaction">The reaction object being moved into the calling one.</param>
		/// <returns>The left-hand reaction, now populated with the memory of the argument.</returns>
		Reaction& operator=(Reaction&& movedReaction) = default;

		/// <summary>
		/// The Notify function, used to alert an individual subscriber that the Event they're interested in has new information to share.
		/// </summary>
		/// <param name="eventPublisher">A constant pointer to the Publisher that contains the Event with new information to relay to subscribers.</param>
		virtual void Notify(const EventPublisher* eventPublisher);
		/// <summary>
		/// The virtual destructor for the Reaction class. No special operation is needed, so it may be defaulted.
		/// </summary>
		virtual ~Reaction() = default;
	};
}