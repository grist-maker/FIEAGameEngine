#pragma once
#include "Action.h"

namespace FieaGameEngine
{
	class ActionDecrement final :
		public Action
	{
		RTTI_DECLARATIONS(ActionDecrement, Action);
	protected:
		/// <summary>
		/// The name of the attribute carrying the target integer. This is searched for up the hierarchy by the updating ActionDecrement.
		/// </summary>
		std::string Target;
		/// <summary>
		/// The amount by which the target integer should be decremented.
		/// </summary>
		size_t Step = 0;
		/// <summary>
		/// The array index at which the target integer resides.
		/// </summary>
		size_t Index = 0;
	public:
		/// <summary>
		/// Default constructor for the ActionDecrement class. This creates a default, base object of the ActionDecrement class, not any of its derivatives, and accepts no arguments,
		/// with no return.
		/// </summary>
		ActionDecrement();

		/// <summary>
		/// The default copy constructor for the ActionDecrement class, copying the right-hand side ActionDecrement to create an entirely new ActionDecrement with functionally equal
		/// data. No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedAction">The ActionDecrement object being copied into the newly-constructed one.</param>
		ActionDecrement(const ActionDecrement& copiedAction) = default;
		/// <summary>
		/// The default move constructor for the ActionDecrement class, moving the right-hand side ActionDecrement's memory and data into the newly constructed ActionDecrement in a
		/// shallow copy. The newly constructed ActionDecrement is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedAction">The ActionDecrement object being moved into the newly-constructed one.</param>
		ActionDecrement(ActionDecrement&& movedAction) = default;
		/// <summary>
		/// The default copy assignment operator for the ActionDecrement class, deep copying the right-hand side ActionDecrement to populate the calling ActionDecrement with
		/// functionally equal data. No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedAction">The ActionDecrement object being copied into the left-hand one.</param>
		/// <returns>The calling ActionDecrement, now functionally equal to the argument provided.</returns>
		ActionDecrement& operator=(const ActionDecrement& copiedAction) = default;
		/// <summary>
		/// The default move assignment operator for the ActionDecrement class, moving the right-hand side ActionDecrement's memory and data into the calling ActionDecrement in a
		/// shallow copy. The left-hand ActionDecrement is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedAction">The ActionDecrement object being moved into the calling one.</param>
		/// <returns>The left-hand ActionDecrement, now populated with the memory of the argument.</returns>
		ActionDecrement& operator=(ActionDecrement&& movedAction) = default;
		/// <summary>
		/// The destructor for the ActionDecrement class. No special work needs to be done, so operation is defaulted.
		/// </summary>
		~ActionDecrement() = default;

		/// <summary>
		/// Provides a list of signatures, each signature representing a prescribed attribute for the ActionDecrement class. This is used to populate each instance properly and automatically
		/// on ActionDecrement object creation.
		/// </summary>
		/// <returns>A vector populated with the signatures for each attribute prescribed for the ActionDecrement class.</returns>
		static Vector<Signature> Signatures();
		/// <summary>
		/// The update method is used to adjust the state of the current ActionDecrement. It operates using a GameTime instance recording current time within the running game. 
		/// </summary>
		/// <param name="currentTime">The GameTime instance representing the time the game is currently at.</param>
		virtual void Update(const GameTime& currentTime);
	};
	ConcreteFactory(ActionDecrement, Scope);
}