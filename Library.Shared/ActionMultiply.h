#pragma once
#include "Action.h"

namespace FieaGameEngine
{
	class ActionMultiply final :
		public Action
	{
		RTTI_DECLARATIONS(ActionMultiply, Action);
	protected:
		/// <summary>
		/// The name of the target attribute holding integers to be multiplied. An upward search is performed by the updating ActionMultiply to find this attribute.
		/// </summary>
		std::string Target = "";
		/// <summary>
		/// The amount by which the target integer is to be divided.
		/// </summary>
		size_t Multiplier = 0;
		/// <summary>
		/// The index at which the target integer resides within an integer array.
		/// </summary>
		size_t Index = 0;
	public:
		/// <summary>
		/// Default constructor for the ActionMultiply class. This creates a default, base object of the ActionMultiply class, not any of its derivatives, and accepts no arguments,
		/// with no return.
		/// </summary>
		ActionMultiply();
		/// <summary>
		/// The default copy constructor for the ActionMultiply class, copying the right-hand side ActionMultiply to create an entirely new ActionMultiply with functionally equal
		/// data. No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedAction">The ActionMultiply object being copied into the newly-constructed one.</param>
		ActionMultiply(const ActionMultiply& copiedAction) = default;
		/// <summary>
		/// The default move constructor for the ActionMultiply class, moving the right-hand side ActionMultiply's memory and data into the newly constructed ActionMultiply in a
		/// shallow copy. The newly constructed ActionMultiply is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedAction">The ActionMultiply object being moved into the newly-constructed one.</param>
		ActionMultiply(ActionMultiply&& movedAction) = default;
		/// <summary>
		/// The default copy assignment operator for the ActionMultiply class, deep copying the right-hand side ActionMultiply to populate the calling ActionMultiply with
		/// functionally equal data. No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedAction">The ActionMultiply object being copied into the left-hand one.</param>
		/// <returns>The calling ActionMultiply, now functionally equal to the argument provided.</returns>
		ActionMultiply& operator=(const ActionMultiply& copiedAction) = default;
		/// <summary>
		/// The default move assignment operator for the ActionMultiply class, moving the right-hand side ActionMultiply's memory and data into the calling ActionMultiply in a
		/// shallow copy. The left-hand ActionMultiply is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedAction">The ActionMultiply object being moved into the calling one.</param>
		/// <returns>The left-hand ActionMultiply, now populated with the memory of the argument.</returns>
		ActionMultiply& operator=(ActionMultiply&& movedAction) = default;
		/// <summary>
		/// The destructor for the ActionMultiply class. No special work needs to be done, so operation is defaulted.
		/// </summary>
		~ActionMultiply() = default;

		/// <summary>
		/// Provides a list of signatures, each signature representing a prescribed attribute for the ActionMultiply class. This is used to populate each instance properly and automatically
		/// on ActionMultiply object creation.
		/// </summary>
		/// <returns>A vector populated with the signatures for each attribute prescribed for the ActionMultiply class.</returns>
		static Vector<Signature> Signatures();
		/// <summary>
		/// The update method is used to adjust the state of the current ActionMultiply. It operates using a GameTime instance recording current time within the running game. 
		/// </summary>
		/// <param name="currentTime">The GameTime instance representing the time the game is currently at.</param>
		virtual void Update(const GameTime& currentTime);
	};
	ConcreteFactory(ActionMultiply, Scope);
}