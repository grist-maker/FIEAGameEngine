#pragma once
#include "Action.h"
namespace FieaGameEngine
{
	/// <summary>
	/// The concrete ActionList class, derived from the abstract Action class. It is used to hold lists of Actions that it may manage, as well as being a named Action itself.
	/// </summary>
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action);
	public:
		/// <summary>
		/// Default constructor for the ActionList class. Creates a new basic object of the ActionList class, using the overloaded Action constructor that accepts a size_t typeid
		/// value.
		/// </summary>
		ActionList();
		/// <summary>
		/// The update function overload for the ActionList class. This calls update on all nested Actions that the ActionList contains based on the GameTime variable provided.
		/// </summary>
		/// <param name="currentTime">The GameTime instance representing the current time within the game. This influences the object's current state as specified within
		/// the update function specification in each derived from Action class.</param>
		virtual void Update(const GameTime& currentTime) override;
		/// <summary>
		/// The signatures method overload for ActionList. This adds an additional prescribed attribute: The Actions table that stores Action nested scopes. Each of these nested scopes
		/// is managed by the action list, which will update it and contain it as needed.
		/// </summary>
		/// <returns>A vector of prescribed attribute signatures for the ActionList class.</returns>
		static Vector<Signature> Signatures();
	protected:
		/// <summary>
		/// A special overload of the ActionList constructor, this one accepting a size_t argument specifying the typeId for the ActionList derived class.
		/// </summary>
		/// <param name="typeId">The unique class ID for the ActionList derived class being constructed.</param>
		ActionList(size_t typeId);
	};
	ConcreteFactory(ActionList, Scope);
}