#pragma once
#include "ActionList.h"
namespace FieaGameEngine
{	
	/// /// <summary>
	/// The ActionListIf class, used to allow action block execution to be specified in the format of an If/Else statement based on the value of a Condition attribute. This allows the definition of a TrueBlock, a container
	/// (or several) of actions to be executed if the condition is true, as well as a FalseBlock, containers of actions to be executed if the condition is false.
	/// </summary>
	class ActionListIf :
		public Action
	{
		RTTI_DECLARATIONS(ActionListIf, Action);
	public:
		/// <summary>
		/// The default constructor for the ActionListIf class. This just calls the overloaded Action constructor with the unique TypeId for the ActionListIf class to construct a new instance of this class.
		/// No other special work needs to be done.
		/// </summary>
		ActionListIf();
		/// <summary>
		/// The Update method for the ActionListIf class. This updates one of the nested ActionList blocks, either TrueBlock or FalseBlock, based on the condition's current value. This operates like an If/Else statement.
		/// </summary>
		/// <param name="currentTime">The current in-game time specified as a const reference to a GameTime instance.</param>
		virtual void Update(const GameTime& currentTime) override;
		/// <summary>
		/// The signatures method for the ActionListIf class. This specifies the prescribed attributes for the base Action class, as well as three new ones: Condition (an integer determining whether to execute the true
		/// or false block of actions), TrueBlock (A table for the one or several action lists containing Actions to execute when the condition is true), and FalseBlock (A table for the one or several action lists containing
		/// actions to execute when the condition is false).
		/// </summary>
		/// <returns>A Vector of signatures specifying all necessary attributes for each ActionListIf instance.</returns>
		static Vector<Signature> Signatures();
	private:
		/// <summary>
		/// A size_t indicating which block of actions should be updated. 0 is false, while any other value is true.
		/// </summary>
		size_t Condition = 0;
	};
	ConcreteFactory(ActionListIf, Scope);
}