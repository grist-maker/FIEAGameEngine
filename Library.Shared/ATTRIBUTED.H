#pragma once
#include "Scope.h"
#include "TypeManager.h"
#include <cassert>
#include <algorithm>

namespace FieaGameEngine
{
	/// <summary>
	/// The Attributed class. Used to allow representation of derived classes with class-specific elements. That is, elements of the class are instantiated with
	/// preset, class-specific attributes already added.
	/// </summary>
	class Attributed: public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope);
	protected:
		/// <summary>
		/// The constructor for the Attributed class, taking in a single necessary argument. This argument is an RTTI::IdType value that specifies the ID for the Attributed derrived class,
		/// which is used to find the datum values expected for objects of that class. Sets up the Attributed instance with all expected class datum.
		/// </summary>
		/// <param name="typeId">The </param>
		Attributed(RTTI::IdType typeId);

	public:
		/// <summary>
		/// The destructor for the Attributed class, clearing all data and freeing all allocated memory to prevent memory leaks. Called automatically on object destruction, but may also be
		/// explicitly invoked.
		/// </summary>
		~Attributed() = default;
		/// <summary>
		/// The copy constructor for the Attributed class. Takes in an Attributed object reference argument to deep copy into the newly constructed Attributed object. Upon completion, both the argument
		/// and constructed Attributed are separate, and changes in either will not affect the other.
		/// </summary>
		/// <param name="copiedAttributed">The attributed object to have its data copied into the newly constructed Attributed.</param>
		Attributed(const Attributed& copiedAttributed);
		/// <summary>
		/// The move constructor for the attributed class. Takes in an Attributed object reference argument to shallow copy, or move, into the newly constructed Attributed object. Upon completion, the
		/// argument Attributed object is no longer usable, but the newly constructed one contains direct pointers to all of its previous data.
		/// </summary>
		/// <param name="movedAttributed">The attributed object to have its data shallowly moved into the newly constructed Attributed.</param>
		Attributed(Attributed&& movedAttributed) noexcept;

		/// <summary>
		/// The copy assignment operator for the Attributed class. Takes in an Attributed object reference argument to deep copy into the left-hand Attributed object. Upon completion, both the argument
		/// and calling Attributed are separate, and changes in either will not affect the other.
		/// </summary>
		/// <param name="copiedAttributed">The attributed object to have its data copied into the newly constructed Attributed.</param>
		/// <returns>A reference to an Attributed object that is a deep copy of the provided argument.</returns>
		Attributed& operator=(const Attributed& copiedAttributed);
		/// <summary>
		/// The move assignment operator for the Attributed class. Takes in an Attributed object reference argument to shallow copy, or move, into the left hand Attributed object. Upon completion, the
		/// argument Attributed object is no longer usable, but the calling one contains direct pointers to all of its previous data.
		/// </summary>
		/// <param name="movedAttributed">The attributed object to have its data shallowly moved into the calling Attributed.</param>
		/// <returns>A reference to an Atttributed object that is a shallow copy of the provided argument.</returns>
		Attributed& operator=(Attributed&& movedAttributed) noexcept;

	private:
		/// <summary>
		/// Populates the calling attributed with all datum members specified as prescribed attributes. Upon completion, the Attributed has all datum members specified by its class definition
		/// with the proper names and order.
		/// </summary>
		void Populate(RTTI::IdType typeId);
		/// <summary>
		/// Does a second pass over previously copied or moved data to ensure all needed attributes are present in the new Attributed object. Additionally, external storage is set
		/// where necessary. This lowers overhead compared to the populate call by not using the unnecessary Append call since assumedly all needed key values have already been added.
		/// </summary>
		void SetExternalStorage(RTTI::IdType typeId);

	public:
		/// <summary>
		/// A boolean function that accepts a string key argument, then searches for an attribute with the same name. Returns true if the attribute exists within the Attributed, and false otherwise.
		/// </summary>
		/// <param name="name">The string key associated with the target attribute.</param>
		/// <returns>A boolean indicating whether or not an attribute with the given name is present in the calling Attributed object.</returns>
		bool IsAttribute(const std::string& name) const;
		/// <summary>
		/// A boolean function that accepts a string key argument, then searches for a prescribed (class-specified) attribute with the same name. Returns true if the prescribed attribute exists within
		/// the Attributed, and false otherwise.
		/// </summary>
		/// <param name="name">The string key associated with the target prescribed attribute.</param>
		/// <returns>A boolean indicating whether or not a prescribed attribute with the given name is present in the calling Attributed object.</returns>
		bool IsPrescribedAttribute(const std::string& name) const;
		/// <summary>
		/// A boolean function that accepts a string key argument, then searches for an auxiliary (instance-specific) attribute with the same name. Returns true if the auxiliary attribute exists
		/// within the Attributed, and false otherwise.
		/// </summary>
		/// <param name="name">The string key associated with the target auxiliary attribute.</param>
		/// <returns>A boolean indicating whether or not an auxiliary attribute with the given name is present in the calling Attributed object.</returns>
		bool IsAuxiliaryAttribute(const std::string& name) const;

		/// <summary>
		/// The function used to append new auxiliary (instance-specific) attributes onto the Attributed object. Will not complete if a prescribed attribute exists with the same key. If there is already
		/// an exisitng auxiliary attribute with the same name, a reference to this exisitng datum is returned instead of adding a new Datum. Otherwise, a new datum is created and its reference is returned.
		/// </summary>
		/// <param name="name">The key to be associated with the newly added datum.</param>
		/// <returns>A Datum reference to the newly added or existing Datum object.</returns>
		Datum& AppendAuxiliaryAttribute(const std::string& name);

		/// <summary>
		/// Returns a reference to a constant vector of both the auxiliary and prescribed attributes that exist within the calling Attributed object. This makes up all Attributes (key Datum pairs)
		/// inside of the Attributed object.
		/// </summary>
		/// <returns>A constant Vector reference made up of all attributes (key datum pairs) inside of the calling Attributed object.</returns>
		std::pair<size_t, size_t> GetAttributes() const;
		/// <summary>
		/// Returns a reference to a constant vector of all prescribed attributes that exist within the calling Attributed object. This makes up all Attributes (key Datum pairs)	
		/// specified by the Attributed's class inside of the Attributed object.
		/// </summary>
		/// <returns>A constant Vector reference made up of all prescribed (class-specified) attributes (key datum pairs) inside of the calling Attributed object.</returns>
		std::pair<size_t, size_t> GetPrescribedAttributes() const;
		/// <summary>
		/// Returns a reference to a constant vector of all auxiliary attributes that exist within the calling Attributed object. This makes up all Attributes (key Datum pairs)	
		/// specified by this Attributed instance that were not provided by its class.
		/// </summary>
		/// <returns>A constant Vector reference made up of all prescribed (class-specified) attributes (key datum pairs) inside of the calling Attributed object.</returns>
		std::pair<size_t, size_t> GetAuxiliaryAttributes() const;
		
		/// <summary>
		/// Accesses a pointer to any Datum member that exists in the Attributed, performing a search for the Datum associated with the string key provided.
		/// </summary>
		/// <param name="key">The string key associated with the target datum value.</param>
		/// <returns>A pointer to the Datum value found for the given key, returning nullptr if not found.</returns>
		Datum* At(const std::string& key) const;
		/// <summary>
		/// Accesses a Datum member that exists in the Attributed, accessing the Datum added at the numeric place specified by the index.
		/// </summary>
		/// <param name="index">The index associated with the target datum value.</param>
		/// <returns>The Datum value found for the given index.</returns>
		Datum& At(size_t index) const;
		/// <summary>
		/// Returns the number of elements within the Attributed object. That is, the number of total attributes.
		/// </summary>
		/// <returns>A size_t matching the number of attributes inside the Attributed object.</returns>
		size_t Size() const;
	};
}