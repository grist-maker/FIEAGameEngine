#pragma once
#include "ActionList.h"
namespace FieaGameEngine
{
	/// <summary>
	/// The ActionListWhile class, used to specify while loops based on a specific condition, executing different action containers based on condition and specified operation. There may be a pre-action block that is executed
	/// before entering a while loop, a loop body block that is executed within the while loop, and an increment block that is executed after each loop body execution before the condition is checked again.
	/// </summary>
	class ActionListWhile :
		public Action
	{
		RTTI_DECLARATIONS(ActionListWhile, Action);
	public:
		/// <summary>
		/// The default constructor for the ActionListWhile class. This just calls the overloaded Action constructor with the unique TypeId for the ActionListWhile class to construct a new instance of this class.
		/// No other special work needs to be done.
		/// </summary>
		ActionListWhile();
		/// <summary>
		/// The update method override for the ActionListWhile class. This will effectively execute a while loop as long as its condition prescribed attribute remains non-zero. This entails the use of three logical segments
		/// of ActionLists or Actions. The first section, specified in the Preamble prescribed attribute, is updated once before the while loop is entered. The next section, specified in the LoopAction prescribed
		/// attribute, executes inside of the loop body when entered, on each execution. The final section, specified in the Increment prescribed attribute, is executed directly after the LoopAction execution, right
		/// before the loop condition is checked again.
		/// </summary>
		/// <param name="currentTime">A const reference to the current in-game time.</param>
		virtual void Update(const GameTime& currentTime) override;
		/// <summary>
		/// The Signatures method for ActionListWhile, specifying all prescribed attributes inside the base Action class, as well as four new ones in Condition, LoopAction, Preamble, and Increment to be included in every
		/// instance of the ActionListWhile class.
		/// </summary>
		/// <returns>A signature vector specifying all prescribed attributes to be added to ActionListWhile instances.</returns>
		static Vector<Signature> Signatures();
		/// <summary>
		/// A size_t specifying the condition determining while loop execution.
		/// </summary>
	private:
		size_t Condition = 0;
	};
	ConcreteFactory(ActionListWhile, Scope);
}