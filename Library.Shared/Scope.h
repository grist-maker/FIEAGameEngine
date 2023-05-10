#pragma once
#include "HashMap.h"
#include "Datum.h"
#include <gsl/gsl>
#include <cassert>
#include <algorithm>
#include <memory>
#include "Factory.h"

namespace FieaGameEngine
{
	/// <summary>
	/// The scope class, which is also an RTTI pointer, used to manage tables and nested tables of Datum elements, each associated to a string value as in a HashMap. It manages a hierarchy of both the nest structure of
	/// the storage unit and the order in which elements were added. Allows the user to append new datum, append new scope, access each scope and contained members, and reparent existing scopes. Composed of a Vector
	/// and Hashmap data structure.
	/// </summary>
	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Scope, RTTI);

	public:
		friend Attributed;

		friend Factory<Scope>;
		//template <typename T>
		//friend Factory<T>;
		/// <summary>
		/// Default constructor for scope, allowing the specification of a single element representing the number of spaces to reserve for data values. Otherwise, the value is defaulted to one.
		/// </summary>
		/// <param name="capacity">The number of spaces for elements to be reserved for in advance by the Scope.</param>
		explicit Scope(size_t capacity = 1);
		/// <summary>
		/// Default scope destructor. It is used to fully clear the Scope, as well as free any allocated memory it contains.
		/// </summary>
		virtual ~Scope();
		/// <summary>
		/// Copy constructor for the Scope data object. Creates a deep copy of the scope argument given within the newly created Scope object. The Scope argument and new Scope are then independent and remain intact for 
		/// future use.
		/// </summary>
		/// <param name="copiedScope">The Scope being deep copied into the newly constructed Scope.</param>
		Scope(const Scope& copiedScope);
		/// <summary>
		/// Move constructor for the Scope data object. Creates a shallow copy of the scope argument given within the new created Scope object. The Scope argument provided will be unusable after the assignment takes place.
		/// </summary>
		/// <param name="movedScope">The Scope to be shallow copied into the newly constructed one.</param>
		Scope(Scope&& movedScope) noexcept;

		/// <summary>
		/// Copy assignment operator for the Scope data object.Creates a deep copy of the scope argument given within the left hand Scope object.The Scope argument and new Scope are then independent and remain intact for
		/// future use.
		/// </summary>
		/// <param name="copiedScope">The scope to be deep copied into the left hand side.</param>
		/// <returns>A reference to the newly copied Scope value.</returns>
		Scope& operator=(const Scope& copiedScope);

		Scope& operator=(Scope&& movedScope) noexcept;
		/// <summary>
		/// A bracket operator override for the Scope class. When a valid string key existing within the calling Scope is provided, a reference to the associated Datum object is returned.
		/// </summary>
		/// <param name="datumName">The key associated to the targeted Datum object.</param>
		/// <returns>The datum reference stored at the target key.</returns>
		Datum& operator[](const std::string& datumName);
		/// <summary>
		/// A bracket operator override for the Scope class. When a numeric index is provided, a reference to the Datum stored chronologically at that position is returned. An argument of 2 will return the second Datum added
		/// to the Scope, and so on.
		/// </summary>
		/// <param name="datumIndex">The chronological order in which the target Datum was added.</param>
		/// <returns>A reference to the Datum added at the specified chronological point.</returns>
		Datum& operator[](size_t datumIndex);
		/// <summary>
		/// The equality comparison operator for Scope. Compares every element, ignoring parent hierarchy, by key and associated value. Supports comparison for all Datum types and returns a boolean indicating whether or not
		/// the two Scopes are equal.
		/// </summary>
		/// <param name="comparedScope">The right hand scope being compared to the calling scope.</param>
		/// <returns>A boolean indicating whether or not the two Scopes are equal.</returns>
		[[nodiscard]]bool operator==(const Scope& comparedScope) const;
		/// <summary>
		/// The inequality comparison operator for Scope. Compares every element, ignoring parent hierarchy, by key and associated value. Supports comparison for all Datum types and returns a boolean indicating whether or not
		/// the two Scopes are not equal.
		/// </summary>
		/// <param name="comparedScope">The right hand scope being compared to the calling scope.</param>
		/// <returns>A boolean indicating whether or not the two Scopes are not equal.</returns>
		[[nodiscard]]bool operator!=(const Scope& comparedScope) const;

		/// <summary>
		/// Searches within the calling datum (no higher or lower in hierarchy) to find a Datum value associated with the provided key. A Datum* corresponding to the located element is returned
		/// if found, otherwise returning nullptr.
		/// </summary>
		/// <param name="key">The key associated with the targeted Datum.</param>
		/// <returns>A Datum* associated to the targeted element</returns>
		[[nodiscard]] Datum* Find(const std::string& key) const;
		/// <summary>
		/// Searches within the calling datum and its ancestors to find a target value. Takes two arguments: one being the key to the target Datum, and the other being the scope address in which
		/// the datum was found. The address of the target datum is returned on completion if found, otherwise returning nullptr.
		/// </summary>
		/// <param name="key">The key associated with the target datum.</param>
		/// <param name="foundScope">The scope housing the found datum. Passed by reference and automatically updates the argument's value with execution.</param>
		/// <returns>The datum pointer variable, if found, otherwise nullptr.</returns>
		[[nodiscard]] Datum* Search(const std::string& key, Scope*& foundScope);
		/// <summary>
		/// Searches within the calling datum and its ancestors to find a target value. Takes one argument: being the key to the target Datum. The address of the target datum is returned
		/// on completion if found, otherwise returning nullptr.
		/// </summary>
		/// <param name="key">The key associated with the target datum.</param>
		/// <returns>The datum pointer variable, if found, otherwise nullptr.</returns>
		[[nodiscard]] Datum* Search(const std::string& key) const;

		/// <summary>
		/// Adds a new datum value onto the back of the calling Scope. Order of entry is preserved in the OrderTable to keep track of all elements. If the key already exists within the Scope,
		/// simply returns the existing Datum.
		/// </summary>
		/// <param name="datumName">The key to be associated with the new or existing Datum</param>
		/// <returns>A reference to the datum that was found or created.</returns>
		Datum& Append(const std::string& datumName);
		/// <summary>
		/// Adds a new Scope value onto the back of the calling Scope's datum. Order of entry is preserved in the OrderTable to keep track of all elements. If the key already exists within
		/// the Scope that is not of type table or unknown, the operation fails. The new scope is parented to the calling scope.
		/// </summary>
		/// <param name="datumName">The key to be associated with the new or existing scope</param>
		/// <returns>A reference to the Scope that was created.</returns>
		Scope& AppendScope(const std::string& name);

		/// <summary>
		/// A function that parents a nested or root scope to another. Upon completion, the calling scope has the child scope placed within its hierarchy, as long as the calling scope is not equal to
		/// or an ancestor of the child. It is stored in a datum with the provided string key. 
		/// </summary>
		/// <param name="child">A reference to the Scope to be nested inside the calling scope.</param>
		/// <param name="childKey">The key to be associated with the nested scope in its new home.</param>
		void Adopt(Scope* child, const std::string& childKey);
		/// <summary>
		/// A function that, when called by a nested scope, derives from it a new root scope while breaking its existing parental and upper hierarchical connections. Its memory must be deleted
		/// by the caller upon its execution, or there is a risk of memory leaks.
		/// </summary>
		/// <returns>A gsl::owner to the Scope* that is newly orphaned.</returns>
		gsl::owner<Scope*> Orphan(); //Return GSL owner to scope*
		/// <summary>
		/// Retrieves a pointer to the parent scope of the caller, that is, the Scope the caller is nested inside. If nonexistent, nullptr is returned.
		/// </summary>
		/// <returns>A scope* associated to the parent of the calling scope.</returns>
		Scope* GetParent() const; //returns address of scope that owns this one

		/// <summary>
		/// Scans through the upper hierarchy of Scopes to determine whether the calling scope is descended from the Scope argument, that is, if the caller is nested inside of the argument.
		/// </summary>
		/// <param name="targetScope">The scope tested for whether or not it is the ancestor of the calling scope.</param>
		/// <returns>A boolean indicating whether or not the caller is descended from the argument Scope.</returns>
		[[nodiscard]] bool IsDescendantOf(const Scope& targetScope) const;

		/// <summary>
		/// Returns a reference to the Datum added at the chronological index provided. Inputting 1 will return the second value added to the scope, 2 returns the third value, and so on.
		/// </summary>
		/// <param name="index">The chronological order in which the target datum was added.</param>
		/// <returns>The datum added at the provided chronological index.</returns>
		[[nodiscard]]Datum& At(size_t index) const;
		/// <summary>
		/// Finds the datum pointer and index at which the argument provided scope exists, returning both in a pair. If not found, the Datum* is set to nullptr.
		/// </summary>
		/// <param name="targetScope">The scope being searched for within the calling scope.</param>
		/// <returns>A std::pair made up of the Datum* containing the target scope and the index at which it exists in order.</returns>
		[[nodiscard]]std::pair<Datum*, size_t> FindContainedScope(const Scope* targetScope) const;
		protected:
		/// <summary>
		/// Creates a copy of the calling scope within a new scope object, whose memory is returned as pointer value.
		/// </summary>
		/// <returns>The pointer storing the allocated memory containing the copied scope object.</returns>
	//	virtual Scope* Clone() const;
		virtual Scope* Clone() const;
		public:
		/// <summary>
		/// Fully wipes all data and frees the memory allocated by the calling scope. Additionally frees that of nested scopes within it, ensuring lack of memory leaks and that deletion or
		///  reassignment can proceed for the Scope object cleared.
		/// </summary>
		void Clear();
		/// <summary>
		/// Returns a size_t variable indicating the number of elements stored within the Scope.
		/// </summary>
		/// <returns>A size_t indicating the number of elements stored in the calling scope.</returns>
		[[nodiscard]]size_t Size() const;

		void DeepCopy(const Scope& other);

		const std::pair<std::string, const Datum> GetPair(size_t index) const;

	protected:
		/// <summary>
		/// A hierarchical organized map of all datum and scopes comprising the associated scope. Formed from a hashmap that stores string Datum pairs, allowing names to be tied to different
		/// data entries and allowing fast lookup of these names to find associated datum and scope values.
		/// </summary>
		HashMap<const std::string, Datum> ScopeData;
		/// <summary>
		/// A chronological list documenting the order in which all datum elements were added to the Scope. Made up of a vector that stores string datum* pairs, allowing chronological access
		/// based on the order values were added in.
		/// </summary>
		Vector <std::pair<const std::string, Datum>*> OrderTable;
		/// <summary>
		/// A pointer to the scope that contains the current scope, if it is not a root scope. If it is a root, the value is defaulted to nullptr, and is reset similarly when orphan is called.
		/// </summary>
		Scope* Parent{ nullptr };
	};

	ConcreteFactory(Scope, Scope);
};