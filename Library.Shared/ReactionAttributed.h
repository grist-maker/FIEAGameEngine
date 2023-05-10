#pragma once
#include "Reaction.h"
#include "Factory.h"
#include "EventMessageAttributed.h"
#include "Event.h"

namespace FieaGameEngine
{
	/// <summary>
	/// The ReactionAttributed class can hold within it, as auxiliary attributes, potential arguments for a function call that it may make on Event notification. ReactionAttributed objects are thus considered simply reactions
	/// with additional attributes. They carry a prescribed attribute specifying the subtype that the subscriber is interested in hearing, these subtypes being more specific Events of type EventMessageAttributed. When notified
	/// of a new event of the EventMessageAttributed type and with the matching subtype, it copies all of the Event payload's auxiliary attributes into itself, which can now act as data for future operation.
	/// </summary>
	class ReactionAttributed : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction);
	protected:
		/// <summary>
		/// The overloaded constructor that accepts a typeId variable to create new classes derived from ReactionAttributed.
		/// </summary>
		/// <param name="typeId">The RTTI ID for the derived type being constructed.</param>
		explicit ReactionAttributed(const size_t typeId);
		/// <summary>
		/// An array of strings representing the Subtype of Event<EventMessageAttributed> that the subscriber is interested in hearing from. There may be several, so any Event with a subtype listed within this array will
		/// trigger an update.
		/// </summary>
		std::string Subtype[3];
		/// <summary>
		/// The update method override for ReactionAttributed. This is triggered not on tick, but in response to an Event notification that is accepted by the ReactionAttributed object.
		/// </summary>
		/// <param name="currentTime">The current in-game time.</param>
		virtual void Update(const GameTime& currentTime) override;
		/// <summary>
		/// A private helper function that's used to copy all auxiliary attributes contained in an EventMessageAttributed object into the calling ReactionAttributed. This provides checking
		/// for prescribed attributes, only reassigning the value if the data types are both the same.
		/// </summary>
		/// <param name="eventPublisher">The EventMessageAttributed object that the ReactionAttributed is being notified of, and thus, the one that supplies the auxiliary attribute
		/// function parameters for the ReactionAttributed to use.</param>
		void CopyAuxiliaryAttributes(const EventMessageAttributed& eventPublisher);
	
	public:
		/// <summary>
		/// Default constructor for the ReactionAttributed class. This creates a default, base object of the ReactionAttributed class, not any of its derivatives, and accepts no arguments, with
		/// no return.
		/// </summary>
		ReactionAttributed();
		/// <summary>
		/// The default copy constructor for the reactionAttributed class, copying the right-hand side reactionAttributed to create an entirely new reactionAttributed with functionally equal data. No special
		/// work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedReactioAttributed">The reactionAttributed object being copied into the newly-constructed one.</param>
		ReactionAttributed(const ReactionAttributed& copiedReactionAttributed) = default;
		/// <summary>
		/// The default move constructor for the reactionAttributed class, moving the right-hand side reactionAttributed's memory and data into the newly constructed reaction in a shallow copy. The
		/// newly constructed reactionAttributed is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedReactionAttributed">The reactionAttributed object being moved into the newly-constructed one.</param>
		ReactionAttributed(ReactionAttributed&& movedReactionAttributed) = default;
		/// <summary>
		/// The default copy assignment operator for the ReactionAttributed class, deep copying the right-hand side reactionAttributed to populate the calling ReactionAttributed with functionally equal data.
		/// No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedReactionAttributed">The ReactionAttributed object being copied into the left-hand one.</param>
		/// <returns>The calling ReactionAttributed, now functionally equal to the argument provided.</returns>
		ReactionAttributed& operator=(const ReactionAttributed& copiedReactionAttributed) = default;
		/// <summary>
		/// The default move assignment operator for the ReactionAttributed class, moving the right-hand side ReactionAttributed's memory and data into the calling ReactionAttributed in a shallow copy. The
		/// left-hand ReactionAttributed is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedReactionAttribted">The reactionAttributed object being moved into the calling one.</param>
		/// <returns>The left-hand reactionAttributed, now populated with the memory of the argument.</returns>
		ReactionAttributed& operator=(ReactionAttributed&& movedReactionAttributed) = default;
		/// <summary>
		/// The destructor for the ReactionAttributed class. It is here that it unsubscribes from the Event<EventMessageAttributed> messages.
		/// </summary>
		virtual ~ReactionAttributed();

		/// <summary>
		/// The Notify function, used to alert an individual subscriber that the Event they're interested in has new information to share. This one only accepts Attributed events, and proceeds if its
		/// subtype matches its own. If true, it copies over the attribute arguments into itself, and calls the Action update function.
		/// </summary>
		/// <param name="eventPublisher">A constant pointer to the Publisher that contains the Event with new information to relay to subscribers.</param>
		virtual void Notify(const EventPublisher* eventPublisher) override;

		/// <summary>
		/// The static Signatures method for the ReactionAttributed class. This specifies the prescribed attribute "Subtype" to denote Event subtypes that the ReactionAttributed is interested in, as well
		/// as those provided within ActionList objects.
		/// </summary>
		/// <returns>A Vector of signatures specifying each prescribed attribute for the ReactionAttributed object.</returns>
		static Vector<Signature> Signatures();
	};
	ConcreteFactory(ReactionAttributed, Scope);
}