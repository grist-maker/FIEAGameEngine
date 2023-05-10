#pragma once
#include "Attributed.h"
#include "GameState.h"

namespace FieaGameEngine
{
	/// <summary>
	/// The action class, used to represent actions that a GameObject can take within a game. They perform some defined behavior, and can be given a name to suit their purpose within
	/// a game. They may also respond to changes in time within a game via their virtual Update function, which must be overriden for each specific concrete Action derived instance.
	/// </summary>
	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed);
	protected:
		/// <summary>
		/// A non-default constructor for the Action class, used to allow the creation of instances of a class derived from Action. This is done by allowing the specification of a
		/// typeId, a size_t variable corresponding to the unique RTTI ID associated with the derived class.
		/// </summary>
		/// <param name="typeId">The typeId for the derived from action class being instantiated.</param>
		explicit Action(const size_t typeId);
		/// <summary>
		/// The name of the Action, stored as a string variable.
		/// </summary>
		std::string Name;
	public:
		/// <summary>
		/// Default constructor for the Action class. This creates a default, base object of the Action class, not any of its derivatives, and accepts no arguments, with
		/// no return.
		/// </summary>
		Action();
		/// <summary>
		/// The default copy constructor for the action class, copying the right-hand side action to create an entirely new action with functionally equal data. No special
		/// work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedAction">The action object being copied into the newly-constructed one.</param>
		Action(const Action& copiedAction) = default;
		/// <summary>
		/// The default move constructor for the action class, moving the right-hand side action's memory and data into the newly constructed action in a shallow copy. The
		/// newly constructed action is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedAction">The action object being moved into the newly-constructed one.</param>
		Action(Action&& movedAction) = default;
		/// <summary>
		/// The default copy assignment operator for the action class, deep copying the right-hand side action to populate the calling action with functionally equal data.
		/// No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedAction">The action object being copied into the left-hand one.</param>
		/// <returns>The calling action, now functionally equal to the argument provided.</returns>
		Action& operator=(const Action& copiedAction) = default;
		/// <summary>
		/// The default move assignment operator for the action class, moving the right-hand side action's memory and data into the calling action in a shallow copy. The
		/// left-hand action is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedAction">The action object being moved into the calling one.</param>
		/// <returns>The left-hand action, now populated with the memory of the argument.</returns>
		Action& operator=(Action&& movedAction) = default;
		/// <summary>
		/// The destructor for the Action class. No special work needs to be done, so operation is defaulted.
		/// </summary>
		~Action() = default;

		/// <summary>
		/// Provides a list of signatures, each signature representing a prescribed attribute for the Action class. This is used to populate each instance properly and automatically
		/// on Action object creation.
		/// </summary>
		/// <returns>A vector populated with the signatures for each attribute prescribed for the Action base class.</returns>
		static Vector<Signature> Signatures();
		/// <summary>
		/// The update method is used to adjust the state of the current action. It must be overriden by derived actions to perform any special behaviors necessary. It operates using 
		/// a GameTime instance recording current time within the running game. 
		/// </summary>
		/// <param name="currentTime">The GameTime instance representing the time the game is currently at.</param>
		virtual void Update(const GameTime& currentTime) = 0;

		/// <summary>
		/// Used to retrieve the name of the target Action, returning it as a constant reference to the string specified within the prescribed "Name" attribute.
		/// </summary>
		/// <returns>A const std::string reference variable corresponding to the string stored within the prescribed "Name" attribute.</returns>
		const std::string& GetName() const;

		/// <summary>
		/// Sets the name of the object, effectively changing the string value that the prescribed "Name" attribute refers to.
		/// </summary>
		/// <param name="newName">The desired name for the calling action.</param>
		void SetName(const std::string& newName);

		/// <summary>
		/// A loop through nested Actions inside of a specific Datum. This loop function is used by ActionList, ActionListWhile, and ActionListIf to dive into nested Actions and update them appropriately, so it is
		/// defined in the base datum class for easy access and code reuse.
		/// </summary>
		/// <param name="targetDatum">A pointer to the Datum being descended into.</param>
		/// <param name="currentTime">A const reference to the current Game Time.</param>
		void UpdateNestedActions(Datum* targetDatum, const GameTime& currentTime);
	};
}