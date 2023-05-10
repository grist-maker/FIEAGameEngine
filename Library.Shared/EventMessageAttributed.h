#pragma once
#include "Attributed.h"

namespace FieaGameEngine
{
	/// <summary>
	/// This class exists to create Attributed derived objects that use their attribute names and values to denote functional arguments. These arguments can be used as input to functions that
	/// subscribers call in response to Event<EventMessageAttributed> message receipt. This is an automated method of triggering function calls based on change in condition, similarly to
	/// OnTriggerEnter behaviors.
	/// </summary>
	class EventMessageAttributed final : public Attributed
	{
		RTTI_DECLARATIONS(EventMessageAttributed, Attributed);
	protected:
		/// <summary>
		/// The overloaded constructor that accepts a typeId variable to create new classes derived from EventMessageAttributed.
		/// </summary>
		/// <param name="typeId">The RTTI ID for the derived type being constructed.</param>
		explicit EventMessageAttributed(size_t typeId);
		/// <summary>
		/// The subtype for the EventMessageAttributed class. This specifies the exact subtype of event that its associated Event is a part of. This denotes a more specific type of sub-Event
		/// being triggered by the main Event.
		/// </summary>
		std::string Subtype;

	public:
		/// <summary>
		/// Provides a list of signatures, each signature representing a prescribed attribute for the EventMessageAttributed class. This is used to populate each instance properly and automatically
		/// on EventMessageAttributed object creation.
		/// </summary>
		/// <returns>A vector populated with the signatures for each attribute prescribed for the EventMessageAttributed class.</returns>
		static Vector<Signature> Signatures();

		/// <summary>
		/// Default constructor for the EventMessageAttributed class. This creates a default, base object of the EventMessageAttributed class, not any of its derivatives, and has no
		/// necessary arguments, with no return. One argument (defaulted to the empty string) is allowed to set the subtype to the string argument provided on object construction.
		/// </summary>
		/// <param name="subtype">The subtype the newly constructed EventMessageAttributed should have.</param>
		EventMessageAttributed(std::string subtype = "");

		/// <summary>
		/// The default copy constructor for the EventMessageAttributed class, copying the right-hand side EventMessageAttributed object to create an entirely new
		/// EventMessageAttributed with functionally equal data. No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedEventMessage">The EventMessageAttributed object being copied into the newly-constructed one.</param>
		EventMessageAttributed(const EventMessageAttributed& copiedEventMessage) = default;
		/// <summary>
		/// The default move constructor for the EventMessageAttributed class, moving the right-hand side EventMessageAttributed's memory and data into the newly constructed
		/// EventMessageAttributed in a shallow copy. The newly constructed EventMessageAttributed is now the exact same as the right hand side, but it remains valid while
		/// the argument does not. No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="movedEventMessage">The EventMessageAttributed object being moved into the newly-constructed one.</param>
		EventMessageAttributed(EventMessageAttributed&& movedEventMessage) = default;
		/// <summary>
		/// The default copy assignment operator for the EventMessageAttributed class, copying the right-hand side EventMessageAttributed object to give the left hand
		/// EventMessageAttributed functionally equal data. No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedEventMessage">The EventMessageAttributed object being copied into the newly-constructed one.</param>
		EventMessageAttributed& operator=(const EventMessageAttributed& copiedEventMessage) = default;
		/// <summary>
		/// The default move assignment operator for the EventMessageAttributed class, moving the right-hand side EventMessageAttributed's memory and data into the calling
		/// EventMessageAttributed in a shallow copy. The left-hand EventMessageAttributed is now the exact same as the right hand side, but it remains valid while the
		/// argument does not. No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="movedEventMessage">The EventMessageAttributed object being moved into the calling one.</param>
		/// <returns>The left-hand EventMessageAttributed, now populated with the memory of the argument.</returns>
		EventMessageAttributed& operator=(EventMessageAttributed&& movedEventMessage) = default;
		/// <summary>
		/// The destructor for the EventMessageAttributed class. No special operation is needed, so it may be defaulted.
		/// </summary>
		virtual ~EventMessageAttributed() = default;

		/// <summary>
		/// A get method to let the user retrieve the value stored in the EventMessageAttributed's associated subtype string. Returns the value as a const reference to disallow changes to it through
		/// the setter.
		/// </summary>
		/// <returns>A const std::string reference to the Subtype of the EventMessageAttributed.</returns>
		const std::string& GetSubtype() const;
		/// <summary>
		/// A set method to allow a user to easily set the subtype of the EventMessageAttributed from anywhere they wish.
		/// </summary>
		/// <param name="newName">The new string to set the EventMessageAttributed's subtype.</param>
		void SetSubtype(std::string newName);
	};
	ConcreteFactory(EventMessageAttributed, Scope);
}