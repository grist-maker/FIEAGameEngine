#pragma once
#include "Scope.h"
#include "TypeManager.h"
#include "json/json.h"
#include <cassert>
#include <algorithm>
#include <fstream>
#include <sstream>

namespace FieaGameEngine
{
	/// <summary>
	/// A forward declaration of the IJsonParseHelper class, used to prevent cyclic dependency but allow basic access to objects of the type in function arguments.
	/// </summary>
	class IJsonParseHelper;
	/// <summary>
	/// The JsonParseCoordinator is used to manage and coordinate the parsing of Json files for storable data elements it contains. It manages helpers that it can delegate work to, ensuring that
	/// the user interacts with the helper interface as little as possible to ease use. They carry an associated wrapper that is used to store parsed data elements upon the completion of deserializing data.
	/// </summary>
	class JsonParseCoordinator final
	{
	public:
		friend IJsonParseHelper;
		/// <summary>
		/// The embedded wrapper class is used to create a generic, versatile object that can carry a specified data type to transport between the helper and JsonParseCoordinator. It takes parsed JSON
		/// values of a type it supports and stores it for later use defined by the user. It is associated to a JsonParseCoordinator as well, and interacts with those select helpers that can parse the
		/// data type it supports.
		/// </summary>
		class Wrapper : public RTTI
		{
			friend JsonParseCoordinator;
			friend IJsonParseHelper;
			RTTI_DECLARATIONS(Wrapper, RTTI);

		public:
			/// <summary>
			/// A virtual constructor for the Wrapper class, allowing it to be extended by derived classes. This allows it to easily copy itself for the clone method. It returns the newly created Wrapper
			/// as a shared_ptr, ensuring absence of memory leaks and allowing it to be shared when necessary
			/// </summary>
			/// <returns>A shared pointer to the wrapper that has been created.</returns>
			virtual std::shared_ptr<Wrapper> Create() const = 0;
			/// <summary>
			/// The virtual destructor for the Wrapper class. It is pure virtual, doing work as needed by derrived classes. This allows easy extendability by the user.
			/// </summary>
			virtual ~Wrapper() = default;

			virtual void Initialize();
			/// <summary>
			/// Returns the current depth at which the wrapper is located. This is used to aid traversal into nested values as provided through table values.
			/// </summary>
			/// <returns>A size_t variable representing the current depth level of the wrapper. Is 0 whenever a value is not currently being parsed.</returns>
			size_t Depth() const;
			/// <summary>
			/// Used to return a pointer to the JsonParseCoordinator to which the wrapper is associated. Returns it as a pointer, returning a nullptr if a JsonParseCoordinator is not associated with
			/// the calling wrapper.
			/// </summary>
			/// <returns>A pointer to the JsonParseCoordinator object associated to the calling wrapper.</returns>
			JsonParseCoordinator* GetJsonParseCoordinator();

		private:
			/// <summary>
			/// The size_t variable representing the current depth the wrapper is positioned at. Returned by the Depth function and varies during the course of the traversal of the JSON file.
			/// </summary>
			size_t CurrentDepth = 0;

			/// <summary>
			/// Used to set the JsonParseCoordinator to which the wrapper is associated. Takes in its address as a basic pointer, then stores it within the CoordinatorAddress variable for this wrapper.
			/// If the wrapper already has an associated JsonParseCoordinator, this JsonParseCoordinator will have its Wrapper reference set to nullptr and the calling wrapper will be associated to
			/// the provided argument instead.
			/// </summary>
			/// <param name="address">The JsonParseCoordinator pointer to which the wrapper will now be associated.</param>
			void SetJsonParseCoordinator(JsonParseCoordinator* address);
			/// <summary>
			/// Increments the current depth of the stored wrapper, indicating how deep it is in the JSON value being parsed. This function will be called when each new nested level is reached.
			/// </summary>
			void IncrementDepth();
			/// <summary>
			/// Decrements the current depth of the stored wrapper, indicating how deep it is in the JSON value being parsed. This function will be called when a nested level is left to go to the one above.
			/// </summary>
			void DecrementDepth();
			/// <summary>
			/// Stores the JsonParseCoordinator to which this wrapper is associated. It is stored as a raw pointer, and initialized to the nullptr.
			/// </summary>
			JsonParseCoordinator* CoordinatorAddress = nullptr;
		};

		/// <summary>
		/// The copy constructor for the JsonParseCoordinator is not in use. Because of this, it is deleted. Instead, the JsonParseCoordinator may be copied by use of the clone method.
		/// </summary>
		JsonParseCoordinator(JsonParseCoordinator& copy) = delete;
		/// <summary>
		/// The copy assignment for the JsonParseCoordinator is not in use. Because of this, it is deleted. Instead, the JsonParseCoordinator may be copied by use of the clone method.
		/// </summary>
		JsonParseCoordinator& operator=(JsonParseCoordinator& copy) = delete;
		
		/// <summary>
		/// The base constructor for the JsonParseCoordinator. It has no defaulted variation, and always accepts a single argument, a shared_ptr of the wrapper to which it will be associated.
		/// </summary>
		/// <param name="wrapper">A shared pointer to the wrapper the JsonParseCoordinator will be associated with.</param>
		explicit JsonParseCoordinator(std::shared_ptr<Wrapper> wrapper);
		/// <summary>
		/// The move constructor for the JsonParseCoordinator. This moves all values from the provided argument JsonParseCoordinator directly into the calling JsonParseCoordinator via a shallow copy,
		/// meaning the JsonParseCoordinator provided as an argument may not be used upon completion, as all of its data exists solely in the calling JsonParseCoordinator.
		/// </summary>
		/// <param name="movedCoordinator">The provided JsonParseCoordinator argument, which will be moved into the calling JsonParseCoordinator and then left unusable.</param>
		JsonParseCoordinator(JsonParseCoordinator&& movedCoordinator) noexcept;
		/// <summary>
		/// The move assignment for the JsonParseCoordinator. This moves all values from the provided argument JsonParseCoordinator directly into the calling JsonParseCoordinator via a shallow copy,
		/// meaning the JsonParseCoordinator provided as an argument may not be used upon completion, as all of its data exists solely in the calling JsonParseCoordinator.
		/// </summary>
		/// <param name="movedCoordinator">The provided JsonParseCoordinator argument, which will be moved into the calling JsonParseCoordinator and then left unusable.</param>
		/// <returns>The JsonParseCoordinator holding the newly moved data. This will be usable, with the exact same data as held by the provided argument.</returns>
		JsonParseCoordinator& operator=(JsonParseCoordinator&& movedCoordinator) noexcept;
		/// <summary>
		/// The destructor for the JsonParseCoordinator. This is defaulted since no additional work needs to be done to prepare the object for deletion that is not already provided.
		/// </summary>
		~JsonParseCoordinator() = default;

		/// <summary>
		/// The clone method is used to produce a JsonParseCoordinator with a functionally equal wrapper, as well as Helpers list. The data stored within these objects is not retained. This facilitates
		/// multithreading, letting a user quickly create a functional equivalent JsonParseCoordinator that can parse Json values in tandem with the coordinator it was created from.
		/// </summary>
		/// <returns>A unique_ptr to the JsonParseCoordinator that has been newly produced.</returns>
		std::unique_ptr<JsonParseCoordinator> Clone();

		/// <summary>
		/// Adds a new IJsonParseHelper that may be used and directed by the JsonParseCoordinator to parse values it can handle. An exception will be thrown if the Helper being added has the same address
		/// as one that already exists in the Helpers vector.
		/// </summary>
		/// <param name="newHelper">A shared pointer to the new IJsonParseHelper to be added as a helper for the JsonParseCoordinator.</param>
		void AddHelper(std::shared_ptr<IJsonParseHelper> newHelper);
		/// <summary>
		/// Removes a IJsonParseHelper that may exist in the Helpers Vector. If it is not inside the Vector, no action is taken.
		/// </summary>
		/// <param name="newHelper">A shared pointer to the IJsonParseHelper to be removed from the JsonParseCoordinator.</param>
		void RemoveHelper(std::shared_ptr<IJsonParseHelper> removedHelper);
		/// <summary>
		/// Removes a Helper from the list using its RTTI ID supplied from the previous removeHelper call, or the user. This ensures that there are no two helpers of the same
		/// type in a list, as this is wasteful when searching for a Helper that can handle a specific data type.
		/// </summary>
		/// <param name="HelperId">The type ID for the helper being searched for.</param>
		void RemoveHelper(RTTI::IdType HelperId);
		
		/// <summary>
		/// Deserializes a JSON object from a provided string, then calling the ParseMembers function and populating the wrapper with its nested values.
		/// </summary>
		/// <param name="JSONData">The JSON string to be parsed by the ParseCoordinator's Helpers.</param>
		void DeserializeObject(const std::string& JSONData);
		/// <summary>
		/// Deserializes a JSON object from a provided file, then calling the ParseMembers function and populating the wrapper with its nested values. The file is found based on the string name provided
		/// as an argument.
		/// </summary>
		/// <param name="fileName">The string used to find the file to be parsed by the ParseCoordinator's Helpers.</param>
		void DeserializeObjectFromFile(const std::string& fileName);
		/// <summary>
		/// Deserializes a JSON object from a provided input stream, then calling the ParseMembers function and populating the wrapper with its nested values.
		/// </summary>
		/// <param name="JSONData">The JSON input stream to be parsed by the ParseCoordinator's Helpers.</param>
		void DeserializeObject(std::istream& JSONData);
		
		/// <summary>
		/// Returns a shared_ptr to the JsonParseCoordinator's associated wrapper.
		/// </summary>
		/// <returns>A shared_ptr to the JsonParseCoordinator's associated wrapper</returns>
		std::shared_ptr<Wrapper> GetWrapper();
		/// <summary>
		/// Sets the JsonParseCoordinator's associated wrapper. If it already possesses an associated wrapper, the wrapper has its associated JsonParseCoordinator set to nullptr.
		/// </summary>
		/// <returns>A shared_ptr to the JsonParseCoordinator's associated wrapper</returns>
		void SetWrapper(std::shared_ptr<Wrapper> wrapperAddress);
		/// <summary>
		/// Allows the JsonParseCoordinator to initialize all of its Helpers at once, done before parsing the JSON data.
		/// </summary>
		void Initialize();

		size_t HelperSize();

		const Vector<std::shared_ptr<IJsonParseHelper>>& HelperList();

	private:
		/// <summary>
		/// A vector of Helpers, the IJsonParseHelper pointer variables that can perform work on the behalf of the calling JsonParseCoordinator. Each of these helpers may be able to parse a different
		/// type of data from a JSON file.
		/// </summary>
		Vector<std::shared_ptr<IJsonParseHelper>> Helpers;
		/// <summary>
		/// Used to parse a full Json::Value, done via numerous calls to the Parse function. 
		/// </summary>
		void ParseMembers(const Json::Value& object);
		/// <summary>
		/// Parses a single attribute from a Json::Value. This attribute, if supported for parsing by any of the JsonParseCoordinator's helpers, may be stored within the helper's data.
		/// </summary>
		void Parse(const std::string& valueString, const Json::Value& value);
		/// <summary>
		/// A shared pointer to the wrapper associated with the JsonParseCoordinator.
		/// </summary>
		std::shared_ptr<Wrapper> ContainedWrapper;
	};
}