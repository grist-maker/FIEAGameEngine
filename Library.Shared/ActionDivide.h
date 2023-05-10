#pragma once
#include "Action.h"

namespace FieaGameEngine
{
	class ActionDivide final :
		public Action
	{
		RTTI_DECLARATIONS(ActionDivide, Action);
	protected:
		/// <summary>
		/// The name of the target Attribute to have its contents divided. This is searched for up the hierarchy from the updating ActionDivide.
		/// </summary>
		std::string Target;
		/// <summary>
		/// The divisor, or amount by which the target value is to be divided by.
		/// </summary>
		size_t Divisor = 0;
		/// <summary>
		/// The index, or array position at which the target value resides.
		/// </summary>
		size_t Index = 0;
	public:
		/// <summary>
		/// Default constructor for the ActionDivide class. This creates a default, base object of the ActionDivide class, not any of its derivatives, and accepts no arguments,
		/// with no return.
		/// </summary>
		ActionDivide();
		/// <summary>
		/// The default copy constructor for the ActionDivide class, copying the right-hand side ActionDivide to create an entirely new ActionDivide with functionally equal
		/// data. No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedAction">The ActionDivide object being copied into the newly-constructed one.</param>
		ActionDivide(const ActionDivide& copiedAction) = default;
		/// <summary>
		/// The default move constructor for the ActionDivide class, moving the right-hand side ActionDivide's memory and data into the newly constructed ActionDivide in a
		/// shallow copy. The newly constructed ActionDivide is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedAction">The ActionDivide object being moved into the newly-constructed one.</param>
		ActionDivide(ActionDivide&& movedAction) = default;
		/// <summary>
		/// The default copy assignment operator for the ActionDivide class, deep copying the right-hand side ActionDivide to populate the calling ActionDivide with
		/// functionally equal data. No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedAction">The ActionDivide object being copied into the left-hand one.</param>
		/// <returns>The calling ActionDivide, now functionally equal to the argument provided.</returns>
		ActionDivide& operator=(const ActionDivide& copiedAction) = default;
		/// <summary>
		/// The default move assignment operator for the ActionDivide class, moving the right-hand side ActionDivide's memory and data into the calling ActionDivide in a
		/// shallow copy. The left-hand ActionDivide is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedAction">The ActionDivide object being moved into the calling one.</param>
		/// <returns>The left-hand ActionDivide, now populated with the memory of the argument.</returns>
		ActionDivide& operator=(ActionDivide&& movedAction) = default;
		/// <summary>
		/// The destructor for the ActionDivide class. No special work needs to be done, so operation is defaulted.
		/// </summary>
		~ActionDivide() = default;

		/// <summary>
		/// Provides a list of signatures, each signature representing a prescribed attribute for the ActionDivide class. This is used to populate each instance properly and automatically
		/// on ActionDivide object creation.
		/// </summary>
		/// <returns>A vector populated with the signatures for each attribute prescribed for the ActionDivide class.</returns>
		static Vector<Signature> Signatures();
		/// <summary>
		/// The update method is used to adjust the state of the current ActionDivide. It operates using a GameTime instance recording current time within the running game. 
		/// </summary>
		/// <param name="currentTime">The GameTime instance representing the time the game is currently at.</param>
		virtual void Update(const GameTime& currentTime);
	};
	ConcreteFactory(ActionDivide, Scope);
}