#pragma once
#include "pch.h"
#include "HashMap.h"
#include <cassert>
#include "RTTI.h"
#include "Datum.h"
#include "Vector.h"

/// <summary>
/// Defines the static Type Manager class, as well as the Signature struct. Both work in tandem to allow the automation of adding class-specified attributes, automatically adding those of the proper
/// Datum type and associated key value every time an object of a certain class is instantiated.
/// </summary>
namespace FieaGameEngine
{
	struct Signature final
	{
	public:
		/// <summary>
		/// The Signature struct, providing an easy mechanism to specify each necessary attribute for a class. It requires the key name, datum type, number of elements associated, and memory offset
		/// necessary to be incremented for external storage specification.
		/// </summary>
		/// <param name="name">The name of the key to be associated with the datum. Effectively, this acts as the attribute's name.</param>
		/// <param name="type">The type of data held by the specified attribute.</param>
		/// <param name="size">The number of distinct elements that are stored within the attribute.</param>
		/// <param name="offset">The memory offset needed to avoid overwriting previous data.</param>
		Signature(std::string name, Datum::DatumTypes type, size_t size, size_t offset)
			: Name{ name }, Type{ type }, Size{ size }, Offset{ offset }
		{
		}
		/// <summary>
		/// The name of the key to be associated with the datum. Effectively, this acts as the attribute's name.
		/// </summary>
		std::string Name;
		/// <summary>
		/// The type of data held by the specified attribute.
		/// </summary>
		Datum::DatumTypes Type;
		/// <summary>
		/// The number of distinct elements that are stored within the attribute.
		/// </summary>
		size_t Size;
		/// <summary>
		/// The memory offset needed to avoid overwriting previous data.
		/// </summary>
		size_t Offset;
	};

	/// <summary>
	/// The Type Manager class. This automatically manages the class-specific attributes for all registered types. Every time an item is added of the specified class, it is instantiated with the
	/// preset attributes. It can be created and destroyed at any point by the user. As it is static, it is accessible without explicitly instantiating an object directly.
	/// </summary>
	class TypeManager final
	{
	public:
		/// <summary>
		/// Returns a pointer to the static Type Manager, providing access to all methods and work done by the Type Manager.
		/// </summary>
		/// <returns>A pointer to the static type manager object.</returns>
		static TypeManager* Instance()
		{
			return Manager;
		}
		/// <summary>
		/// Creates a new type manager object, associating it to the Manager variable. This allows the user to access a single instance at any point, giving them the ability to manage the type manager's
		/// allocated memory.
		/// </summary>
		void CreateInstance()
		{
			if (Manager == nullptr)
			{
				Manager = new TypeManager;
			}
		}
		/// <summary>
		/// Frees the memory within the Manager variable. This can be done at any point in time specified by the user.
		/// </summary>
		void DestroyInstance()
		{
			if (Manager != nullptr)
			{
				delete Manager;
				Manager = nullptr;
			}
		}

		void AddSignatures(std::pair<size_t, Vector<Signature>>newPair)
		{
			SignaturesList.Insert(newPair);
		}

		void RemoveSignatures(std::size_t id)
		{
			SignaturesList.Remove(id);
		}
		/// <summary>
		/// Returns a Vector of Signatures, with each signature specifying a different attribute held by the calling deerived class. This can then be iterated through to fully populate any new class instance.
		/// </summary>
		/// <param name="id">The RTTI type ID associated with the calling derived class. This ensures that the Type Manager can get a unique list of signatures for each registered type automatically.</param>
		/// <returns>A constant reference to a Vector of signatures for the calling derived class. This is based on the type ID argument provided.</returns>
		[[nodiscard]] const Vector<Signature>& GetSignatures(std::size_t id)
		{
			assert(TypeManager::Instance() != nullptr);
			return TypeManager::Instance()->SignaturesList[id];
		}
	private:
		/// <summary>
		/// A type manager pointer, used to allow the user to access all methods and operations provided by the class. It is initialized to nullptr, and must be instantiated and destroyed by the user with the
		/// use of the CreateInstance() and DestroyInstance() methods.
		/// </summary>
		inline static TypeManager* Manager{ nullptr };
		/// <summary>
		/// A HashMap that stores all registered signature vectors. This allows all needed types to be registered, with their signature vectors being accessible at a key associated to the unique class type
		/// id.
		/// </summary>
		HashMap < std::size_t, Vector <Signature> > SignaturesList;
	};
}