#pragma once
#include "Action.h"

namespace FieaGameEngine
{
	class ActionIncrement final :
		public Action
	{
		RTTI_DECLARATIONS(ActionIncrement, Action);
	protected:
		/// <summary>
		/// The name of the target attribute containing an integer to be incremented.
		/// </summary>
		std::string Target;
		/// <summary>
		/// The amount by which the target integer should be incremented.
		/// </summary>
		size_t Step = 0;
		/// <summary>
		/// The index in the Integer array of the target integer.
		/// </summary>
		size_t Index = 0;
	public:
		/// <summary>
		/// Default constructor for the ActionIncrement class. This creates a default, base object of the ActionIncrement class, not any of its derivatives, and accepts no arguments,
		/// with no return.
		/// </summary>
		ActionIncrement();
		/// <summary>
		/// The default copy constructor for the ActionIncrement class, copying the right-hand side ActionIncrement to create an entirely new ActionIncrement with functionally equal
		/// data. No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedAction">The ActionIncrement object being copied into the newly-constructed one.</param>
		ActionIncrement(const ActionIncrement& copiedAction) = default;
		/// <summary>
		/// The default move constructor for the ActionIncrement class, moving the right-hand side ActionIncrement's memory and data into the newly constructed ActionIncrement in a
		/// shallow copy. The newly constructed ActionIncrement is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedAction">The ActionIncrement object being moved into the newly-constructed one.</param>
		ActionIncrement(ActionIncrement&& movedAction) = default;
		/// <summary>
		/// The default copy assignment operator for the ActionIncrement class, deep copying the right-hand side ActionIncrement to populate the calling ActionIncrement with
		/// functionally equal data. No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedAction">The ActionIncrement object being copied into the left-hand one.</param>
		/// <returns>The calling ActionIncrement, now functionally equal to the argument provided.</returns>
		ActionIncrement& operator=(const ActionIncrement& copiedAction) = default;
		/// <summary>
		/// The default move assignment operator for the ActionIncrement class, moving the right-hand side ActionIncrement's memory and data into the calling ActionIncrement in a
		/// shallow copy. The left-hand ActionIncrement is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedAction">The ActionIncrement object being moved into the calling one.</param>
		/// <returns>The left-hand ActionIncrement, now populated with the memory of the argument.</returns>
		ActionIncrement& operator=(ActionIncrement&& movedAction) = default;
		/// <summary>
		/// The destructor for the ActionIncrement class. No special work needs to be done, so operation is defaulted.
		/// </summary>
		~ActionIncrement() = default;

		/// <summary>
		/// Provides a list of signatures, each signature representing a prescribed attribute for the ActionIncrement class. This is used to populate each instance properly and automatically
		/// on ActionIncrement object creation.
		/// </summary>
		/// <returns>A vector populated with the signatures for each attribute prescribed for the ActionIncrement class.</returns>
		static Vector<Signature> Signatures();
		/// <summary>
		/// The update method is used to adjust the state of the current ActionIncrement. It operates using a GameTime instance recording current time within the running game. 
		/// </summary>
		/// <param name="currentTime">The GameTime instance representing the time the game is currently at.</param>
		virtual void Update(const GameTime& currentTime);
	};
	ConcreteFactory(ActionIncrement, Scope);
}