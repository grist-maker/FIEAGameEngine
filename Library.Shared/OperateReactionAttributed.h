#pragma once
#include "ReactionAttributed.h"

namespace FieaGameEngine
{ 
    class OperateReactionAttributed final : public ReactionAttributed
    {
    protected:
		/// <summary>
		/// The update method override for OperateReactionAttributed. This is triggered not on tick, but in response to an Event notification that is accepted by the OperateReactionAttributed object. It searches to see
		/// if the object has been given additional attributes after the previous Notify event call, and if it finds the desired attributes specifying step, target, and index, copies those values into each
		/// ActionIncrement, ActionDecrement, ActionMultiply, and ActionDivide within the OperateReactionAttributed's Actions list.
		/// </summary>
		/// <param name="currentTime">The current in-game time.</param>
        virtual void Update(const GameTime& currentTime) override;
		RTTI_DECLARATIONS(OperateReactionAttributed, ReactionAttributed);
	public:
		/// <summary>
		/// Default constructor for the OperateReactionAttributed class. This creates a default, base object of the OperateReactionAttributed class, not any of its derivatives, and accepts no arguments, with
		/// no return.
		/// </summary>
        OperateReactionAttributed();
		/// <summary>
		/// The default copy constructor for the operatereactionAttributed class, copying the right-hand side operatereactionAttributed to create an entirely new operatereactionAttributed with functionally equal data. No special
		/// work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedOperateReactioAttributed">The operateReactionAttributed object being copied into the newly-constructed one.</param>
		OperateReactionAttributed(const OperateReactionAttributed& copiedOperateReactionAttributed) = default;
		/// <summary>
		/// The default move constructor for the OperateReactionAttributed class, moving the right-hand side OperateReactionAttributed's memory and data into the newly constructed reaction in a shallow copy. The
		/// newly constructed OperateReactionAttributed is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedOperateReactionAttributed">The OperateReactionAttributed object being moved into the newly-constructed one.</param>
		OperateReactionAttributed(OperateReactionAttributed&& movedOperateReactionAttributed) = default;
		/// <summary>
		/// The default copy assignment operator for the OperateReactionAttributed class, deep copying the right-hand side OperateReactionAttributed to populate the calling OperateReactionAttributed with functionally equal data.
		/// No special work needs to be done, so operation is defaulted.
		/// </summary>
		/// <param name="copiedOperateReactionAttributed">The OperateReactionAttributed object being copied into the left-hand one.</param>
		/// <returns>The calling OperateReactionAttributed, now functionally equal to the argument provided.</returns>
		OperateReactionAttributed& operator=(const OperateReactionAttributed& copiedOperateReactionAttributed) = default;
		/// <summary>
		/// The default move assignment operator for the OperateReactionAttributed class, moving the right-hand side OperateReactionAttributed's memory and data into the calling OperateReactionAttributed in a shallow copy. The
		/// left-hand OperateReactionAttributed is now the exact same as the right hand side, but it remains valid while the argument does not. No special work needs to be done, so
		/// operation is defaulted.
		/// </summary>
		/// <param name="movedReactionAttribted">The OperateReactionAttributed object being moved into the calling one.</param>
		/// <returns>The left-hand OperateReactionAttributed, now populated with the memory of the argument.</returns>
		OperateReactionAttributed& operator=(OperateReactionAttributed&& movedOperateReactionAttributed) = default;

		/// <summary>
		/// The destructor for the OperateReactionAttributed class. No special work needs to be done, so operation is defaulted.
		/// </summary>
		virtual ~OperateReactionAttributed() = default;

		/// <summary>
		/// The signatures method for the OperateReactionAttributed class. This doesn't add any signatures that are not already in ReactionAttributed. Each of these signatures represents a prescribed attribute
		/// for each instance of the OperateReactionAttributed class.
		/// </summary>
		/// <returns>A static Vector of signatures specifying all prescribed attributes for instances of the class.</returns>
		static Vector<Signature> Signatures();
    };
	ConcreteFactory(OperateReactionAttributed, Scope);
}