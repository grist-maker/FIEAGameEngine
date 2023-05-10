#pragma once
#include "Attributed.h"
#include "Factory.h"
#include "ActionList.h"

namespace FieaGameEngine
{
	/// <summary>
	/// The GameObject class is used to create entities that can act and interact within a game. They can influence game behavior and be derived from to create more specific objects. They include 
	/// necessary attributes, such as rotation, scale, transform, name, and children, and may be customized as needed. They also provide an update function that directs GameObject behavior based on
	/// current time data.
	/// </summary>
	class GameObject : public Attributed
	{
		RTTI_DECLARATIONS(GameObject, Attributed);

	public:
		/// <summary>
		/// Default GameObject constructor. Takes no arguments and creates a basic default constructed GameObject.
		/// </summary>
		GameObject();
		/// <summary>
		/// The default copy constructor. This deep copies over all attributes and their data into the new GameObject being constructed. This means that each GameObject is now equivalent, but can be
		/// controlled separately, so changes in one will not influence the other. Both objects remain valid.
		/// </summary>
		/// <param name="copiedGameObject">The GameObject that is having its data deep-copied into the calling GameObject.</param>
		GameObject(const GameObject& copiedGameObject) = default;
		/// <summary>
		/// The default move constructor for GameObjects. This performs a shallow copy of the GameObject being moved into the calling GameObject. Upon completion, the argument GameObject is invalid and
		/// cannot be used, as its memory has been moved directly into the calling GameObject. The new GameObject is entirely identical to the argument provided.
		/// </summary>
		/// <param name="movedGameObject">The argument GameObject, that which will be moved into the newly constructed GameObject. Upon completion, this object will not be valid.</param>
		GameObject(GameObject&& movedGameObject) = default;
		/// <summary>
		/// The default copy assignment operator. This deep copies over all attributes and their data into the calling GameObject, or left hand side GameObject. This means that each GameObject is now
		/// equivalent, but can be controlled separately, so changes in one will not influence the other. Both objects remain valid.
		/// </summary>
		/// <param name="copiedGameObject">The GameObject that is having its data deep-copied into the calling GameObject.</param>
		/// <returns>A reference to the GameObject that is now a copy of the argument provided.</returns>
		GameObject& operator=(const GameObject& copiedGameObject) = default;
		/// <summary>
		/// The default move assignment for GameObjects. This performs a shallow copy of the GameObject being moved into the calling GameObject. Upon completion, the argument GameObject is invalid and
		/// cannot be used, as its memory has been moved directly into the calling GameObject. The left hand side GameObject is entirely identical to the argument (right hand side GameObject) provided.
		/// </summary>
		/// <param name="movedGameObject">The argument GameObject, that which will be moved into the left-hand GameObject. Upon completion, this object will not be valid.</param>
		/// <returns>A reference to newly move-assigned GameObject, that which is valid.</returns>
		GameObject& operator=(GameObject&& movedGameObject) = default;
		/// <summary>
		/// The destructor for the GameObject class. No special work needs to be done, so it may be defaulted.
		/// </summary>
		~GameObject() = default;

		/// <summary>
		/// The update method is used to adjust the state of GameObjects, their actions, and their children. It may be overriden by derived GameObjects to perform any special behaviors necessary. It operates using 
		/// a GameTime instance recording current time within the running game.
		/// </summary>
		/// <param name="currentTime">The GameTime instance representing the time the game is currently at.</param>
		virtual void Update(const GameTime& currentTime);
		/// <summary>
		/// The signatures method used for creating new GameObject instances. This provides information about all of the prescribed attributes for the GameObject class, allowing its automated construction
		/// for each instance of the GameObject class.
		/// </summary>
		/// <returns>Returns a Vector of the signatures for each prescribed attribute, then used to construct each instance of the GameObject class.</returns>
		static Vector<Signature> Signatures();

		/// <summary>
		/// Returns the datum which contains the list of actions that are possible for this GameObject to take as a pointer. If there is no Actions attribute found, the
		/// nullptr is returned instead.
		/// </summary>
		/// <returns>A constant pointer to the Datum containing the list of available GameObject actions.</returns>
		Datum* Actions() const;
		/// <summary>
		/// Creates a new valid action for the calling GameObject instance. Given a name for the class and the instance object itself, this
		/// </summary>
		/// <param name="className"></param>
		/// <param name="instanceName"></param>
		void CreateAction(const std::string& className, const std::string& instanceName);

	protected:
		/// <summary>
		/// A string variable that represents the name of the GameObject, its prescribed String attribute.
		/// </summary>
		std::string Name;
		/// <summary>
		/// A vector variable that represents the position data of the GameObject, one of its three prescribed vec4 attributes.
		/// </summary>
		glm::vec4 Position = glm::vec4(0, 0, 0, 0);
		/// <summary>
		/// A vector variable that represents the scale data of the GameObject, one of its three prescribed vec4 attributes.
		/// </summary>
		glm::vec4 Scale = glm::vec4(0, 0, 0, 0);
		/// <summary>
		/// A vector variable that represents the rotation data of the GameObject, one of its three prescribed vec4 attributes.
		/// </summary>
		glm::vec4 Rotation = glm::vec4(0, 0, 0, 0);
		/// <summary>
		/// The non-default constructor for the GameObject class, creating derived instances. Takes in a single parameter specifying the typeId. This allows derived classes to provide their own
		/// derived class typeId instead to create more specific instances.
		/// </summary>
		/// <param name="typeId">A size_t variable specifying the unique RTTI typeid for the class being created.</param>
		GameObject(size_t typeId);
	};
	ConcreteFactory(GameObject, Scope);
}