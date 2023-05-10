#pragma once
#include "Action.h"
#include "EventMessageAttributed.h"
#include "Event.h"

namespace FieaGameEngine
{
	/// <summary>
	/// This class is used to create and enqueue new Event<EventMessageAttributed> events with the specified subtype and delay variables. It does this on update calls. It will additionally
	/// copy all of its auxiliary attributes into EventMessageAttributed object to supply as function parameters for the EventSubscriber receiving it.
	/// </summary>
    class ActionEvent : public Action
    {
		RTTI_DECLARATIONS(ActionEvent, Action);
	protected:
		/// <summary>
		/// The Subtype value to be specified on new created Event<EventMessageAttributed> objects. This is a string variable that is used to distinguish between more specific versions of
		/// a base EventMessageAttributed.
		/// </summary>
		std::string Subtype;
		/// <summary>
		/// The Delay (in milliseconds) with which to enqueue new Event<EventMessageAttributed> objects onto the queue. Specified as a size_t variable.
		/// </summary>
		size_t Delay = 0;
		/// <summary>
		/// A private helper function that's used to copy all auxiliary attributes contained in the ActionEvent object into the EventMessageAttributed being created.
		/// </summary>
		/// <param name="newEvent">The EventMessageAttributed object that the ActionEvent is copying its auxiliary attributes into for use as function parameters.</param>
		void CopyAuxiliaryAttributes(EventMessageAttributed& newEvent) const;

	public:
		/// <summary>
		/// Default constructor for the ActionEvent class. This creates a default, base object of the ActionEvent class, not any of its derivatives, and accepts no arguments, with
		/// no return.
		/// </summary>
		ActionEvent();
		/// <summary>
		/// The default copy constructor for the ActionEvent class, copying the right-hand side ActionEvent to create an entirely new ActionEvent with functionally equal data. No special
		/// work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedActionEvent">The ActionEvent object being copied into the newly-constructed one.</param>
		ActionEvent(const ActionEvent& copiedActionEvent) = default;
		/// <summary>
		/// The default move constructor for the ActionEvent class, moving the right-hand side ActionEvent's memory and data into the newly constructed action in a shallow copy. The
		/// newly constructed ActionEvent is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedActionEvent">The ActionEvent object being moved into the newly-constructed one.</param>
		ActionEvent(ActionEvent&& movedActionEvent) = default;
		/// <summary>
		/// The default copy assignment operator for the ActionEvent class, deep copying the right-hand side ActionEvent to populate the calling action with functionally equal data.
		/// No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedActionEvent">The ActionEvent object being copied into the left-hand one.</param>
		/// <returns>The calling ActionEvent, now functionally equal to the argument provided.</returns>
		ActionEvent& operator=(const ActionEvent& copiedActionEvent) = default;
		/// <summary>
		/// The default move assignment operator for the ActionEvent class, moving the right-hand side ActionEvent's memory and data into the calling ActionEvent in a shallow copy. The
		/// left-hand ActionEvent is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedActionEvent">The ActionEvent object being moved into the calling one.</param>
		/// <returns>The left-hand ActionEvent, now populated with the memory of the argument.</returns>
		ActionEvent& operator=(ActionEvent&& movedActionEvent) = default;
		/// <summary>
		/// The destructor for the ActionEvent class. No special work needs to be done, so operation is defaulted.
		/// </summary>
		~ActionEvent() = default;

		/// <summary>
		/// Provides a list of signatures, each signature representing a prescribed attribute for the ActionEvent class. This is used to populate each instance properly and automatically
		/// on ActionEvent object creation.
		/// </summary>
		/// <returns>A vector populated with the signatures for each attribute prescribed for the ActionEvent class.</returns>
		static Vector<Signature> Signatures();
		/// <summary>
		/// The update method is used to create a new Event of EventMessageAttributed object with specified auxiliary parameters and the specified delay to enqueue it at. It operates
		/// using a GameTime instance recording current time within the running game. 
		/// </summary>
		/// <param name="currentTime">The GameTime instance representing the time the game is currently at.</param>
		virtual void Update(const GameTime& currentTime) override;
    };
    ConcreteFactory(ActionEvent, Scope);
}