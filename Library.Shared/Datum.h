#pragma once
#include <cstddef>
#include <string>
#pragma warning(push)
#pragma warning(disable:4201)
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#pragma warning(pop)
#include "RTTI.h"
#include <stdexcept>
#include <memory>
#include <assert.h>

namespace FieaGameEngine
{
	class Attributed;
	class Scope;
	class JsonTableParseHelper;
	/// <summary>
	/// The Datum class is used to contain pointers to elements from a list of supported types. These elements are stored contiguously and can be removed, added, set, stored via internal or
	/// external data storage, and converted to strings.
	/// </summary>
	class Datum
	{
	public:
		friend Scope;
		friend Attributed;
		friend JsonTableParseHelper;
		/// <summary>
		/// Specifies the data type stored within the Datum object, Unknown by default. Ensures operations always use proper datum type.
		/// </summary>
		enum class DatumTypes
		{
			Unknown = 0,
			Integer,
			Float,
			String,
			Vector,
			Matrix,
			Pointer,
			Table
		};
		//Basic constructors
		/// <summary>
		/// Default Datum constructor that takes no arguments. Requires no special behavior since variables are already initialized directly prior.
		/// </summary>
		Datum() = default;
		/// <summary>
		/// Datum constructor that takes a type argument specifying the type of values it will hold.
		/// </summary>
		/// <param name="type">The type of data value to be held by the new datum.</param>
		explicit Datum(DatumTypes type);
		/// <summary>
		/// Datum constructor that takes both a type and size argument, specifying both the type of values to be held and the number of spaces that should be reserved.
		/// </summary>
		/// <param name="type">The type of data value to be held by the new datum.</param>
		/// <param name="size">The number of values to be reserved for the new datum.</param>
		Datum(DatumTypes type, size_t size);

		//Type cast constructors
		/// <summary>
		/// Datum constructor that takes an int value argument. Initializes the Datum with the Integer type and a pointer to the value specified.
		/// </summary>
		/// <param name="value">The integer value to be stored first on the Datum.</param>
		Datum(size_t value);
		/// <summary>
		/// Datum constructor that takes a float value argument. Initializes the Datum with the Float type and a pointer to the value specified.
		/// </summary>
		/// <param name="value">The float value to be stored first on the Datum.</param>
		Datum(float value);
		/// <summary>
		/// Datum constructor that takes a string value argument. Initializes the Datum with the String type and a pointer to the value specified.
		/// </summary>
		/// <param name="value">The string value to be stored first on the Datum.</param>
		Datum(std::string& value);
		/// <summary>
		/// Datum constructor that takes a vector4 value argument from the glm library. Initializes the Datum with the Vector type and a pointer to the value specified.
		/// </summary>
		/// <param name="value">The vector value to be stored first on the Datum.</param>
		Datum(glm::vec4 value);
		/// <summary>
		/// Datum constructor that takes a matrix value argument. Initializes the Datum with the Matrix type and a pointer to the value specified.
		/// </summary>
		/// <param name="value">The matrix value to be stored first on the Datum.</param>
		Datum(glm::mat4& value);
		/// <summary>
		/// Datum constructor that takes an RTTI* value argument. Initializes the Datum with the Pointer type and a pointer to the value specified.
		/// </summary>
		/// <param name="value">The RTTI* value to be stored first on the Datum.</param>
		Datum(RTTI* value);
		Datum(Scope* value);

		/// <summary>
		/// Datum constructor that takes in a starting size_t value and size to reserve for the Datum. Assigns type to Integer, pushes value onto the Datum, and calls reserve to delegate memory.
		/// </summary>
		/// <param name="value">The initial size_t value that should be pointed to on the datum.</param>
		/// <param name="size">The number of element-sized spaces to reserve for the new Datum.</param>
		Datum(size_t value, size_t size);
		/// <summary>
		/// Datum constructor that takes in a starting float value and size to reserve for the Datum. Assigns type to Float, pushes value onto the Datum, and calls reserve to delegate memory.
		/// </summary>
		/// <param name="value">The initial float value that should be pointed to on the datum.</param>
		/// <param name="size">The number of element-sized spaces to reserve for the new Datum.</param>
		Datum(float value, size_t size);
		/// <summary>
		/// Datum constructor that takes in a starting string value reference and size to reserve for the Datum. Assigns type to String, pushes value onto the Datum, and calls reserve to delegate memory.
		/// </summary>
		/// <param name="value">The initial string value that should be pointed to on the datum.</param>
		/// <param name="size">The number of element-sized spaces to reserve for the new Datum.</param>
		Datum(const std::string& value, size_t size);
		/// <summary>
		/// Datum constructor that takes in a starting vector4 value from the glm library and size to reserve for the Datum. Assigns type to Vector, pushes value onto the Datum, and calls reserve to delegate memory.
		/// </summary>
		/// <param name="value">The initial Vector4 value that should be pointed to on the datum.</param>
		/// <param name="size">The number of element-sized spaces to reserve for the new Datum.</param>
		Datum(glm::vec4 value, size_t size);
		/// <summary>
		/// Datum constructor that takes in a starting matrix4x4 value reference from the glm library and size to reserve for the Datum. Assigns type to Matrix, pushes value onto the Datum, and calls reserve to delegate memory.
		/// </summary>
		/// <param name="value">The initial Matrix4x4 value that should be pointed to on the datum.</param>
		/// <param name="size">The number of element-sized spaces to reserve for the new Datum.</param>
		Datum(const glm::mat4& value, size_t size);
		/// <summary>
		/// Datum constructor that takes in a starting RTTI* value and size to reserve for the Datum. Assigns type to Pointer, pushes value onto the Datum, and calls reserve to delegate memory.
		/// </summary>
		/// <param name="value">The initial RTTI* value that should be pointed to on the datum.</param>
		/// <param name="size">The number of element-sized spaces to reserve for the new Datum.</param>
		Datum(RTTI* value, size_t size);

		//Datum copy logic
		/// <summary>
		/// Datum copy constructor that takes in a const Datum reference to be deep-copied into the newly constructed Datum. Preserves the argument Datum as well as the new one, also ensuring
		/// changes to one will not affect the other.
		/// </summary>
		/// <param name="copiedDatum">The Datum to be copied into the newly constructed Datum.</param>
		Datum(const Datum& copiedDatum);
		/// <summary>
		/// Datum copy assignment operator that takes in a const Datum reference to be deep or shallow copied into the calling Datum. Preserves the argument Datum as well as the new one, also ensuring
		/// changes to one will not affect the other.
		/// </summary>
		/// <param name="copiedDatum">The Datum to be copied into the calling Datum.</param>
		/// <returns>A reference to the new copied Datum.</returns>
		Datum& operator=(const Datum& copiedDatum);

		//DatumType scalar assignment operators
		/// <summary>
		/// Datum copy assignment operator for Integer values. Treats the Datum as a scalar and assigns its first and only value as a reference to the provided argument's value. Only works for
		/// Datum of unknown or Integer types, and those that are managed internally. If Datum has existing values, they are cleared prior to assignment.
		/// </summary>
		/// <param name="newValue">The integer value to be assigned to the Datum.</param>
		/// <returns>A reference to the new asigned Datum.</returns>
		Datum& operator=(const size_t newValue);
		/// <summary>
		/// Datum copy assignment operator for Float values. Treats the Datum as a scalar and assigns its first and only value as a reference to the provided argument's value. Only works for
		/// Datum of unknown or Float types, and those that are managed internally. If Datum has existing values, they are cleared prior to assignment.
		/// </summary>
		/// <param name="newValue">The float value to be assigned to the Datum.</param>
		/// <returns>A reference to the new asigned Datum.</returns>
		Datum& operator=(const float newValue);
		/// <summary>
		/// Datum copy assignment operator for String values. Treats the Datum as a scalar and assigns its first and only value as a reference to the provided argument's value. Only works for
		/// Datum of unknown or String types, and those that are managed internally. If Datum has existing values, they are cleared prior to assignment.
		/// </summary>
		/// <param name="newValue">The strring value to be assigned to the Datum.</param>
		/// <returns>A reference to the new asigned Datum.</returns>
		Datum& operator=(const std::string& newValue);
		/// <summary>
		/// Datum copy assignment operator for Vector4 values. Treats the Datum as a scalar and assigns its first and only value as a reference to the provided argument's value. Only works for
		/// Datum of unknown or Vector types, and those that are managed internally. If Datum has existing values, they are cleared prior to assignment.
		/// </summary>
		/// <param name="newValue">The vec4 value to be assigned to the Datum.</param>
		/// <returns>A reference to the new asigned Datum.</returns>
		Datum& operator=(const glm::vec4 newValue);
		/// <summary>
		/// Datum copy assignment operator for Matrix 4x4 values. Treats the Datum as a scalar and assigns its first and only value as a reference to the provided argument's value. Only works for
		/// Datum of unknown or Matrix types, and those that are managed internally. If Datum has existing values, they are cleared prior to assignment.
		/// </summary>
		/// <param name="newValue">The mat4 value to be assigned to the Datum.</param>
		/// <returns>A reference to the new asigned Datum.</returns>
		Datum& operator=(const glm::mat4& newValue);
		/// <summary>
		/// Datum copy assignment operator for RTTI* values. Treats the Datum as a scalar and assigns its first and only value as a reference to the provided argument's value. Only works for
		/// Datum of unknown or Pointer types, and those that are managed internally. If Datum has existing values, they are cleared prior to assignment.
		/// </summary>
		/// <param name="newValue">The RTTI* value to be assigned to the Datum.</param>
		/// <returns>A reference to the new asigned Datum.</returns>
		Datum& operator=(RTTI* newValue);
		//private:
	//	Datum& operator=(Scope*& newValue);

		public:
		//[] operator declaration
		Scope& operator[](size_t index);
		Scope& operator[](size_t index) const;

		//Move logic
		/// <summary>
		/// Move constructor for Datum that makes a shallow copy from the provided Datum argument into the calling Datum. Upon completion, the calling datum is identical to the argument passed,
		/// and the argument is no longer usable.
		/// </summary>
		/// <param name="copiedDatum">The provided data argument that is copied into the calling datum.</param>
		Datum(Datum&& copiedDatum) noexcept;
		/// <summary>
		/// Move assignment operator for Datum that makes a shallow copy from the provided Datum argument into the calling Datum. Upon completion, the calling datum is identical to the argument passed,
		/// and the argument is no longer usable. If the calling datum has existing elements already, they are cleared prior to assignment.
		/// </summary>
		///	<param name="copiedDatum">The provided data argument that is copied into the calling datum.</param>
		Datum& operator=(Datum&& copiedDatum) noexcept;

		//Comparison operators
		/// <summary>
		/// Equality operator that compares the calling and argument-provided Datum, element by element. Does not proceed if the Datum are not of the same type, size, or storage method.
		/// </summary>
		/// <param name="comparedDatum">The Datum being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two Datum are considered functionally equal.</returns>
		bool operator==(const Datum& comparedDatum) const;
		/// <summary>
		/// Inequality operator that compares the calling and argument-provided Datum, element by element. Does not proceed if the Datum are not of the same type, size, or storage method.
		/// </summary>
		/// <param name="comparedDatum">The Datum being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two Datum are considered functionally unequal.</returns>
		bool operator!=(const Datum& comparedDatum) const;
		/// <summary>
		/// Equality operator that compares the calling Datum and argument-provided Integer, treating the datum as a scalar and comparing the first element. Does not proceed if the
		/// Datum is not of the integer type or if the Datum is empty.
		/// </summary>
		/// <param name="comparedDatum">The Integer being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two scalars are considered functionally equal.</returns>
		bool operator==(const size_t& comparedDatum) const;
		/// <summary>
		/// Inequality operator that compares the calling Datum and argument-provided Integer, treating the datum as a scalar and comparing the first element. Does not proceed if the
		/// Datum is not of the integer type or if the Datum is empty.
		/// </summary>
		/// <param name="comparedDatum">The Integer being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two scalars are considered functionally unequal.</returns>
		bool operator!=(const size_t& comparedDatum) const;
		/// <summary>
		/// Equality operator that compares the calling Datum and argument-provided Float, treating the datum as a scalar and comparing the first element. Does not proceed if the
		/// Datum is not of the float type or if the Datum is empty.
		/// </summary>
		/// <param name="comparedDatum">The Float being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two scalars are considered functionally equal.</returns>
		bool operator==(const float& comparedDatum) const;
		/// <summary>
		/// Inequality operator that compares the calling Datum and argument-provided Float, treating the datum as a scalar and comparing the first element. Does not proceed if the
		/// Datum is not of the float type or if the Datum is empty.
		/// </summary>
		/// <param name="comparedDatum">The Float being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two scalars are considered functionally unequal.</returns>
		bool operator!=(const float& comparedDatum) const;
		/// <summary>
		/// Equality operator that compares the calling Datum and argument-provided String, treating the datum as a scalar and comparing the first element. Does not proceed if the
		/// Datum is not of the string type or if the Datum is empty.
		/// </summary>
		/// <param name="comparedDatum">The String being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two scalars are considered functionally equal.</returns>
		bool operator==(const std::string& comparedDatum) const;
		/// <summary>
		/// Inequality operator that compares the calling Datum and argument-provided String, treating the datum as a scalar and comparing the first element. Does not proceed if the
		/// Datum is not of the string type or if the Datum is empty.
		/// </summary>
		/// <param name="comparedDatum">The String being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two scalars are considered functionally unequal.</returns>
		bool operator!=(const std::string& comparedDatum) const;
		/// <summary>
		/// Equality operator that compares the calling Datum and argument-provided Vector4, treating the datum as a scalar and comparing the first element. Does not proceed if the
		/// Datum is not of the vector type or if the Datum is empty.
		/// </summary>
		/// <param name="comparedDatum">The Vector4 being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two scalars are considered functionally equal.</returns>
		bool operator==(const glm::vec4& comparedDatum) const;
		/// <summary>
		/// Inequality operator that compares the calling Datum and argument-provided Vector4, treating the datum as a scalar and comparing the first element. Does not proceed if the
		/// Datum is not of the vector type or if the Datum is empty.
		/// </summary>
		/// <param name="comparedDatum">The Vector4 being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two scalars are considered functionally unequal.</returns>
		bool operator!=(const glm::vec4& comparedDatum) const;
		/// <summary>
		/// Equality operator that compares the calling Datum and argument-provided Matrix4, treating the datum as a scalar and comparing the first element. Does not proceed if the
		/// Datum is not of the matrix type or if the Datum is empty.
		/// </summary>
		/// <param name="comparedDatum">The Matrix 4x4 being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two scalars are considered functionally equal.</returns>
		bool operator==(const glm::mat4& comparedDatum) const;
		/// <summary>
		/// Inequality operator that compares the calling Datum and argument-provided Matrix4, treating the datum as a scalar and comparing the first element. Does not proceed if the
		/// Datum is not of the matrix type or if the Datum is empty.
		/// </summary>
		/// <param name="comparedDatum">The Matrix 4x4 being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two scalars are considered functionally unequal.</returns>
		bool operator!=(const glm::mat4& comparedDatum) const;
		/// <summary>
		/// Equality operator that compares the calling Datum and argument-provided RTTI pointer, treating the datum as a scalar and comparing the first element. Does not proceed if the
		/// Datum is not of the pointer type or if the Datum is empty.
		/// </summary>
		/// <param name="comparedDatum">The RTTI pointer being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two scalars are considered functionally equal.</returns>
		bool operator==(const RTTI* comparedDatum) const;
		/// <summary>
		/// Inequality operator that compares the calling Datum and argument-provided RTTI pointer, treating the datum as a scalar and comparing the first element. Does not proceed if the
		/// Datum is not of the pointer type or if the Datum is empty.
		/// </summary>
		/// <param name="comparedDatum">The RTTI pointer being compared to the calling Datum.</param>
		/// <returns>A boolean indicating whether or not the two scalars are considered functionally unequal.</returns>
		bool operator!=(const RTTI* comparedDatum) const;

		//Destructor
		/// <summary>
		/// The destructor for the Datum object. If elements are stored internally, the data is cleared and the Datum is freed.
		/// </summary>
		~Datum();

		//Type functions
		/// <summary>
		/// Returns the DatumTypes enum value indicating the elements stored inside the Datum.
		/// </summary>
		/// <returns>A DatumTypes enum value corresponding to the stored element type.</returns>
		DatumTypes Type() const;
		/// <summary>
		/// Allows a user to set the DatumTypes enum value indicating the elements stored inside the Datum. Only works if the Datum type is currently Unknown.
		/// </summary>
		/// <param name="type">The DatumType enum value indicating what element type Datum should store.</param>
		void SetType(DatumTypes type);

		//Size functions
		/// <summary>
		/// Returns the size of the Datum, the number of elements currently stored within it.
		/// </summary>
		/// <returns>A size_t set to the number of held elements.</returns>
		size_t Size() const;
		/// <summary>
		/// Returns the capacity of the Datum, the number of spaces reserved for elements within it.
		/// </summary>
		/// <returns>A size_t set to the number of reserved spaces.</returns>
		size_t Capacity() const;

		/// <summary>
		/// Allows the datum to grow or shrink to the size specified. Upon completion, capacity and size are equal. Datum requires a type that is not Unknown to function.
		/// </summary>
		/// <param name="size">The new size and capacity for the Datum.</param>
		void Resize(size_t size);
		/// <summary>
		/// Allows the datum to grow its capacity to the size specified. Does nothing unless the provided size is greater than the current capacity. Does not adjust size or number of elements.
		/// Datum requires a type that is not Unknown to function.
		/// </summary>
		/// <param name="size">The new capacity for the Datum.</param>
		void Reserve(size_t size);

		//Memory removal
		/// <summary>
		/// Removes all existing elements from the Datum without affecting capacity.
		/// </summary>
		void Clear();
		/// <summary>
		/// Changes the capacity and storage space allocated to the Datum to match the size of the datum, the number of elements currently stored.
		/// </summary>
		void ShrinkToFit();

		//Set storage functions
		/// <summary>
		/// Sets external storage for the calling datum. Provided an array of integers and the number of elements for it to hold, the Datum will have external storage set to the array for the
		/// number of indicated elements. Does not work unless Data type is specified to Integer or Unknown, and does not work if the Datum already has elements stored internally.
		/// </summary>
		/// <param name="elementArray">The array to be allocated for external storage.</param>
		/// <param name="elements">The size for the external storage allocation.</param>
		void SetStorage(size_t* elementArray, size_t elements);
		/// <summary>
		/// Sets external storage for the calling datum. Provided an array of floats and the number of elements for it to hold, the Datum will have external storage set to the array for the
		/// number of indicated elements. Does not work unless Data type is specified to Float or Unknown, and does not work if the Datum already has elements stored internally.
		/// </summary>
		/// <param name="elementArray">The storage array to be allocated for external storage.</param>
		/// <param name="elements">The size for the external storage allocation.</param>
		void SetStorage(float* elementArray, size_t elements);
		/// <summary>
		/// Sets external storage for the calling datum. Provided an array of strings and the number of elements for it to hold, the Datum will have external storage set to the array for the
		/// number of indicated elements. Does not work unless Data type is specified to String or Unknown, and does not work if the Datum already has elements stored internally.
		/// </summary>
		/// <param name="elementArray">The storage array to be allocated for external storage.</param>
		/// <param name="elements">The size for the external storage allocation.</param>
		void SetStorage(std::string* elementArray, size_t elements);
		/// <summary>
		/// Sets external storage for the calling datum. Provided an array of Vector4s and the number of elements for it to hold, the Datum will have external storage set to the array for the
		/// number of indicated elements. Does not work unless Data type is specified to Vector or Unknown, and does not work if the Datum already has elements stored internally.
		/// </summary>
		/// <param name="elementArray">The storage array to be allocated for external storage.</param>
		/// <param name="elements">The size for the external storage allocation.</param>
		void SetStorage(glm::vec4* elementArray, size_t elements);
		/// <summary>
		/// Sets external storage for the calling datum. Provided an array of Matrix 4x4s and the number of elements for it to hold, the Datum will have external storage set to the array for the
		/// number of indicated elements. Does not work unless Data type is specified to Matrix or Unknown, and does not work if the Datum already has elements stored internally.
		/// </summary>
		/// <param name="elementArray">The storage array to be allocated for external storage.</param>
		/// <param name="elements">The size for the external storage allocation.</param>
		void SetStorage(glm::mat4* elementArray, size_t elements);
		/// <summary>
		/// Sets external storage for the calling datum. Provided an array of RTTI pointers and the number of elements for it to hold, the Datum will have external storage set to the array for the
		/// number of indicated elements. Does not work unless Data type is specified to RTTI* or Unknown, and does not work if the Datum already has elements stored internally.
		/// </summary>
		/// <param name="elementArray">The storage array to be allocated for external storage.</param>
		/// <param name="elements">The size for the external storage allocation.</param>
		void SetStorage(RTTI** elementArray, size_t elements);

		//Set functions
		/// <summary>
		/// Sets the specified index in the array with the provided Integer value. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Integer DatumType.
		/// </summary>
		/// <param name="value">The integer value to be set at the specified index.</param>
		/// <param name="index">The index referring to the value to be changed in the existing datum.</param>
		void SetInt(size_t value, size_t index = 0);
		/// <summary>
		/// Sets the specified index in the array with the provided Float value. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Float DatumType.
		/// </summary>
		/// <param name="value">The float value to be set at the specified index.</param>
		/// <param name="index">The index referring to the value to be changed in the existing datum.</param>
		void SetFloat(float value, size_t index = 0);
		/// <summary>
		/// Sets the specified index in the array with the provided String value. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// String DatumType.
		/// </summary>
		/// <param name="value">The string value to be set at the specified index.</param>
		/// <param name="index">The index referring to the value to be changed in the existing datum.</param>
		void SetString(std::string& value, size_t index = 0);
		/// <summary>
		/// Sets the specified index in the array with the provided Vector4 value. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Vector DatumType.
		/// </summary>
		/// <param name="value">The vector4 value to be set at the specified index.</param>
		/// <param name="index">The index referring to the value to be changed in the existing datum.</param>
		void SetVector(glm::vec4 value, size_t index = 0);
		/// <summary>
		/// Sets the specified index in the array with the provided Matrix value. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Matrix DatumType.
		/// </summary>
		/// <param name="value">The matrix 4x4 value to be set at the specified index.</param>
		/// <param name="index">The index referring to the value to be changed in the existing datum.</param>
		void SetMatrix(glm::mat4& value, size_t index = 0);
		/// <summary>
		/// Sets the specified index in the array with the provided RTTI pointer value. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Pointer DatumType.
		/// </summary>
		/// <param name="value">The RTTI* value to be set at the specified index.</param>
		/// <param name="index">The index referring to the value to be changed in the existing datum.</param>
		void SetRTTI(RTTI* value, size_t index = 0);
		private:
		void SetScope(Scope* value, size_t index = 0);
		public:
		//Get functions
		/// <summary>
		/// Gets the non-const Int value stored at the specified index in the array. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Integer DatumType.
		/// </summary>
		/// <param name="index">The index referring to the value to be retrieved from the Datum.</param>
		/// <returns>The integer value held within the specified index.</returns>
		size_t& GetInt(size_t index = 0);
		/// <summary>
		/// Gets the non-const Float value stored at the specified index in the array. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Float DatumType.
		/// </summary>
		/// <param name="index">The index referring to the value to be retrieved from the Datum.</param>
		/// <returns>The float value held within the specified index.</returns>
		float& GetFloat(size_t index = 0);
		/// <summary>
		/// Gets the non-const String value stored at the specified index in the array. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// String DatumType.
		/// </summary>
		/// <param name="index">The index referring to the value to be retrieved from the Datum.</param>
		/// <returns>The string value held within the specified index.</returns>
		std::string& GetString(size_t index = 0);
		/// <summary>
		/// Gets the non-const Vec4 value stored at the specified index in the array. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Vector DatumType.
		/// </summary>
		/// <param name="index">The index referring to the value to be retrieved from the Datum.</param>
		/// <returns>The Vector4 value held within the specified index.</returns>
		glm::vec4& GetVector(size_t index = 0);
		/// <summary>
		/// Gets the non-const Mat4 value stored at the specified index in the array. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Matrix DatumType.
		/// </summary>
		/// <param name="index">The index referring to the value to be retrieved from the Datum.</param>
		/// <returns>The Matrix 4x4 value held within the specified index.</returns>
		glm::mat4& GetMatrix(size_t index = 0);
		/// <summary>
		/// Gets the non-const RTTI* value stored at the specified index in the array. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Pointer DatumType.
		/// </summary>
		/// <param name="index">The index referring to the value to be retrieved from the Datum.</param>
		/// <returns>The RTTI* value held within the specified index.</returns>
		RTTI*& GetRTTI(size_t index = 0);
		Scope*& GetScope(size_t index = 0);

		public:
		/// <summary>
		/// Gets the const Int value stored at the specified index in the array. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Integer DatumType.
		/// </summary>
		/// <param name="index">The index referring to the value to be retrieved from the Datum.</param>
		/// <returns>The const integer value held within the specified index.</returns>
		const size_t GetConstInt(size_t index = 0) const;
		/// <summary>
		/// Gets the const Float value stored at the specified index in the array. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Float DatumType.
		/// </summary>
		/// <param name="index">The index referring to the value to be retrieved from the Datum.</param>
		/// <returns>The const float value held within the specified index.</returns>
		const float GetConstFloat(size_t index = 0) const;
		/// <summary>
		/// Gets the const String value stored at the specified index in the array. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// String DatumType.
		/// </summary>
		/// <param name="index">The index referring to the value to be retrieved from the Datum.</param>
		/// <returns>The const string value held within the specified index.</returns>
		const std::string& GetConstString(size_t index = 0) const;
		/// <summary>
		/// Gets the const Vec4 value stored at the specified index in the array. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Vector DatumType.
		/// </summary>
		/// <param name="index">The index referring to the value to be retrieved from the Datum.</param>
		/// <returns>The const Vector4 value held within the specified index.</returns>
		const glm::vec4 GetConstVector(size_t index = 0) const;
		/// <summary>
		/// Gets the const Mat4 value stored at the specified index in the array. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Matrix DatumType.
		/// </summary>
		/// <param name="index">The index referring to the value to be retrieved from the Datum.</param>
		/// <returns>The const Matrix 4x4 value held within the specified index.</returns>
		const glm::mat4& GetConstMatrix(size_t index = 0) const;
		/// <summary>
		/// Gets the const RTTI* value stored at the specified index in the array. Index is 0 by default. Does not work if the index provided is greater than the size or if the Datum is not of the
		/// Pointer DatumType.
		/// </summary>
		/// <param name="index">The index referring to the value to be retrieved from the Datum.</param>
		/// <returns>The const RTTI* value held within the specified index.</returns>
		RTTI*const& GetConstRTTI(size_t index = 0) const;
		Scope*const& GetConstScope(size_t index = 0) const;

		public:
		//PushBack functions
		/// <summary>
		/// Pushes a new value onto the back of the Datum. If size is equal to capacity, capacity increases by one to accommodate it. Does not work if Datum type is anything besides Unknown
		/// or Integer.
		/// </summary>
		/// <param name="newElement">The Integer to be pushed to the back of the calling Datum.</param>
		void PushBack(size_t newElement);
		/// <summary>
		/// Pushes a new value onto the back of the Datum. If size is equal to capacity, capacity increases by one to accommodate it. Does not work if Datum type is anything besides Unknown
		/// or Float.
		/// </summary>
		/// <param name="newElement">The Float to be pushed to the back of the calling Datum.</param>
		void PushBack(float newElement);
		/// <summary>
		/// Pushes a new value onto the back of the Datum. If size is equal to capacity, capacity increases by one to accommodate it. Does not work if Datum type is anything besides Unknown
		/// or String.
		/// </summary>
		/// <param name="newElement">The String to be pushed to the back of the calling Datum.</param>
		void PushBack(const std::string& newElement);
		/// <summary>
		/// Pushes a new value onto the back of the Datum. If size is equal to capacity, capacity increases by one to accommodate it. Does not work if Datum type is anything besides Unknown
		/// or Vector.
		/// </summary>
		/// <param name="newElement">The Vec4 to be pushed to the back of the calling Datum.</param>
		void PushBack(glm::vec4 newElement);
		/// <summary>
		/// Pushes a new value onto the back of the Datum. If size is equal to capacity, capacity increases by one to accommodate it. Does not work if Datum type is anything besides Unknown
		/// or Matrix.
		/// </summary>
		/// <param name="newElement">The Mat4 to be pushed to the back of the calling Datum.</param>
		void PushBack(const glm::mat4& newElement);
		/// <summary>
		/// Pushes a new value onto the back of the Datum. If size is equal to capacity, capacity increases by one to accommodate it. Does not work if Datum type is anything besides Unknown
		/// or Pointer.
		/// </summary>
		/// <param name="newElement">The RTTI* to be pushed to the back of the calling Datum.</param>
		void PushBack(RTTI* newElement);
		private:
		void PushBack(Scope* newElement);
		
		public:
		//PopBack functions
		/// <summary>
		/// Pops the last value off of the back of the Datum. Does not work if the Datum is empty. Decrements size by one if successful without affecting capacity.
		/// </summary>
		void PopBack();

		//Front functions
		/// <summary>
		/// Returns the size_t value at the front of the Datum. Does not work if Datum is empty or its type is not Integer.
		/// <returns>An size_t value with the same value held by the pointer at the start of the Integer Datum.</returns>
		/// </summary>
		size_t& FrontInt();
		/// <summary>
		/// Returns the float value at the front of the Datum. Does not work if Datum is empty or its type is not Float.
		/// <returns>A float value with the same value held by the pointer at the start of the Float Datum.</returns>
		/// </summary>
		float& FrontFloat();
		/// <summary>
		/// Returns the string value at the front of the Datum. Does not work if Datum is empty or its type is not String.
		/// <returns>A string value with the same value held by the pointer at the start of the String Datum.</returns>
		/// </summary>
		std::string& FrontString();
		/// <summary>
		/// Returns the Vector4 value at the front of the Datum. Does not work if Datum is empty or its type is not Vector.
		/// <returns>A Vector4 value with the same value held by the pointer at the start of the Vector Datum.</returns>
		/// </summary>
		glm::vec4& FrontVector();
		/// <summary>
		/// Returns the Matrix4 value at the front of the Datum. Does not work if Datum is empty or its type is not Matrix.
		/// <returns>A matrix4x4 value with the same value held by the pointer at the start of the Matrix Datum.</returns>
		/// </summary>
		glm::mat4& FrontMatrix();
		/// <summary>
		/// Returns the RTTI* value at the front of the Datum. Does not work if Datum is empty or its type is not Pointer.
		/// <returns>A RTTI* value with the same value held by the pointer at the start of the Pointer Datum.</returns>
		/// </summary>
		RTTI*& FrontRTTI();

		/// <summary>
		/// Returns the const size_t value at the front of the Datum. Does not work if Datum is empty or its type is not Integer.
		/// <returns>A const size_t value with the same value held by the pointer at the start of the Integer Datum.</returns>
		/// </summary>
		const size_t FrontConstInt() const;
		/// <summary>
		/// Returns the const float value at the front of the Datum. Does not work if Datum is empty or its type is not Float.
		/// <returns>A const float value with the same value held by the pointer at the start of the Float Datum.</returns>
		/// </summary>
		const float FrontConstFloat() const;
		/// <summary>
		/// Returns the const string value at the front of the Datum. Does not work if Datum is empty or its type is not String.
		/// <returns>A const string value with the same value held by the pointer at the start of the String Datum.</returns>
		/// </summary>
		const std::string& FrontConstString() const;
		/// <summary>
		/// Returns the const Vector4 value at the front of the Datum. Does not work if Datum is empty or its type is not Vector.
		/// <returns>A const Vector4 value with the same value held by the pointer at the start of the Vector Datum.</returns>
		/// </summary>
		const glm::vec4 FrontConstVector() const;
		/// <summary>
		/// Returns the const Matrix4 value at the front of the Datum. Does not work if Datum is empty or its type is not Matrix.
		/// <returns>A const matrix4x4 value with the same value held by the pointer at the start of the Matrix Datum.</returns>
		/// </summary>
		const glm::mat4 FrontConstMatrix() const;
		/// <summary>
		/// Returns the const RTTI* value at the front of the Datum. Does not work if Datum is empty or its type is not Pointer.
		/// <returns>A const RTTI* value with the same value held by the pointer at the start of the Pointer Datum.</returns>
		/// </summary>
		RTTI*const& FrontConstRTTI() const;
		
		//Back functions
		/// <summary>
		/// Returns the size_t value at the back of the Datum. Does not work if Datum is empty or its type is not Integer.
		/// <returns>An size_t value with the same value held by the pointer at the back of the Integer Datum.</returns>
		/// </summary>
		size_t& BackInt();
		/// <summary>
		/// Returns the float value at the back of the Datum. Does not work if Datum is empty or its type is not Float.
		/// <returns>A float value with the same value held by the pointer at the back of the Float Datum.</returns>
		/// </summary>
		float& BackFloat();
		/// <summary>
		/// Returns the string value at the back of the Datum. Does not work if Datum is empty or its type is not String.
		/// <returns>A string value with the same value held by the pointer at the back of the String Datum.</returns>
		/// </summary>
		std::string& BackString();
		/// <summary>
		/// Returns the vector4 value at the back of the Datum. Does not work if Datum is empty or its type is not Vector.
		/// <returns>A vector value with the same value held by the pointer at the back of the Vector Datum.</returns>
		/// </summary>
		glm::vec4& BackVector();
		/// <summary>
		/// Returns the matrix 4x4 value at the back of the Datum. Does not work if Datum is empty or its type is not Matrix.
		/// <returns>A matrix value with the same value held by the pointer at the back of the Matrix Datum.</returns>
		/// </summary>
		glm::mat4& BackMatrix();
		/// <summary>
		/// Returns the RTTI* value at the back of the Datum. Does not work if Datum is empty or its type is not Pointer.
		/// <returns>An RTTI* value with the same value held by the pointer at the back of the RTTI* Datum.</returns>
		/// </summary>
		RTTI*& BackRTTI();

		/// <summary>
		/// Returns the const size_t value at the back of the Datum. Does not work if Datum is empty or its type is not Integer.
		/// <returns>A const size_t value with the same value held by the pointer at the back of the Integer Datum.</returns>
		/// </summary>
		const size_t BackConstInt() const;
		/// <summary>
		/// Returns the const float value at the back of the Datum. Does not work if Datum is empty or its type is not Float.
		/// <returns>A const float value with the same value held by the pointer at the back of the Float Datum.</returns>
		/// </summary>
		const float BackConstFloat() const;
		/// <summary>
		/// Returns the const string value at the back of the Datum. Does not work if Datum is empty or its type is not String.
		/// <returns>A const string value with the same value held by the pointer at the back of the String Datum.</returns>
		/// </summary>
		const std::string& BackConstString() const;
		/// <summary>
		/// Returns the const vector4 value at the back of the Datum. Does not work if Datum is empty or its type is not Vector.
		/// <returns>A const vector value with the same value held by the pointer at the back of the Vector Datum.</returns>
		/// </summary>
		const glm::vec4 BackConstVector() const;
		/// <summary>
		/// Returns the const matrix 4x4 value at the back of the Datum. Does not work if Datum is empty or its type is not Matrix.
		/// <returns>A const matrix value with the same value held by the pointer at the back of the Matrix Datum.</returns>
		/// </summary>
		const glm::mat4& BackConstMatrix() const;
		/// <summary>
		/// Returns the const RTTI* value at the back of the Datum. Does not work if Datum is empty or its type is not Pointer.
		/// <returns>A const RTTI* value with the same value held by the pointer at the back of the RTTI* Datum.</returns>
		/// </summary>
		RTTI*const& BackConstRTTI() const;

		//Remove functions
		/// <summary>
		/// Removes the first Integer with a specified value from the Datum. Does not work if the Datum is empty, not of the Integer type, or the element is not inside it.
		/// Decrements size by one if successful without affecting capacity.
		/// </summary>
		/// <returns>A boolean indicating whether the element was found and removed.</returns>
		/// <param name="value">The integer value that should be searched for and removed.</param>
		bool Remove(size_t value);
		/// <summary>
		/// Removes the first Float with a specified value from the Datum. Does not work if the Datum is empty, not of the Float type, or the element is not inside it.
		/// Decrements size by one if successful without affecting capacity.
		/// </summary>
		/// <returns>A boolean indicating whether the element was found and removed.</returns>
		/// <param name="value">The float value that should be searched for and removed.</param>
		bool Remove(float value);
		/// <summary>
		/// Removes the first String with a specified value from the Datum. Does not work if the Datum is empty, not of the String type, or the element is not inside it.
		/// Decrements size by one if successful without affecting capacity.
		/// </summary>
		/// <returns>A boolean indicating whether the element was found and removed.</returns>
		/// <param name="value">The string value that should be searched for and removed.</param>
		bool Remove(const std::string& value);
		/// <summary>
		/// Removes the first Vector with a specified value from the Datum. Does not work if the Datum is empty, not of the Vector type, or the element is not inside it.
		/// Decrements size by one if successful without affecting capacity.
		/// </summary>
		/// <returns>A boolean indicating whether the element was found and removed.</returns>
		/// <param name="value">The vector4 value that should be searched for and removed.</param>
		bool Remove(glm::vec4 value);
		/// <summary>
		/// Removes the first Matrix with a specified value from the Datum. Does not work if the Datum is empty, not of the Matrix type, or the element is not inside it.
		/// Decrements size by one if successful without affecting capacity.
		/// </summary>
		/// <returns>A boolean indicating whether the element was found and removed.</returns>
		/// <param name="value">The Matrix 4x4 value that should be searched for and removed.</param>
		bool Remove(const glm::mat4& value);
		/// <summary>
		/// Removes the first RTTI* with a specified value from the Datum. Does not work if the Datum is empty, not of the Pointer type, or the element is not inside it.
		/// Decrements size by one if successful without affecting capacity.
		/// </summary>
		/// <returns>A boolean indicating whether the element was found and removed.</returns>
		/// <param name="value">The RTTI* value that should be searched for and removed.</param>
		bool Remove(RTTI* value);

		/// <summary>
		/// Removes the value at the corresponding index from the Datum. Does not work if the index exceeds or is equal to the size of the Datum.
		/// Decrements size by one if successful without affecting capacity.
		/// </summary>
		/// <returns>A boolean indicating whether the element was removed.</returns>
		/// <param name="index">The size_t value specifying the data value index to be removed from the Datum.</param>
		bool RemoveAt(size_t index);
		
		//Find functions
		/// <summary>
		/// Searches for an integer in the Datum with the provided value. Does not work if Datum is empty or Datum Type is not Integer. If found, returns a
		/// size_t with the target value, setting the size_t to the size of the Datum otherwise.
		/// </summary>
		/// <returns>A size_t indicating what index the target value was found at, set to the end of the Datum if not found.</returns>
		/// <param name ="value">Int value to be searched for within the Datum.</param>
		size_t Find(size_t value) const;
		/// <summary>
		/// Searches for a float in the Datum with the provided value. Does not work if Datum is empty or Datum Type is not Float. If found, returns a
		/// size_t with the target value, setting the size_t to the size of the Datum otherwise.
		/// </summary>
		/// <returns>A size_t indicating what index the target value was found at, set to the end of the Datum if not found.</returns>
		/// <param name ="value">Float value to be searched for within the Datum.</param>
		size_t Find(float value) const;
		/// <summary>
		/// Searches for a string in the Datum with the provided value. Does not work if Datum is empty or Datum Type is not String. If found, returns a
		/// size_t with the target value, setting the size_t to the size of the Datum otherwise.
		/// </summary>
		/// <returns>A size_t indicating what index the target value was found at, set to the end of the Datum if not found.</returns>
		/// <param name ="value">String value to be searched for within the Datum.</param>
		size_t Find(const std::string& value) const;
		/// <summary>
		/// Searches for a Vector4 in the Datum with the provided value. Does not work if Datum is empty or Datum Type is not Vector. If found, returns a
		/// size_t with the target value, setting the size_t to the size of the Datum otherwise.
		/// </summary>
		/// <returns>A size_t indicating what index the target value was found at, set to the end of the Datum if not found.</returns>
		/// <param name ="value">Vector4 value to be searched for within the Datum.</param>
		size_t Find(glm::vec4 value) const;
		/// <summary>
		/// Searches for a Matrix4 in the Datum with the provided value. Does not work if Datum is empty or Datum Type is not Matrix. If found, returns a
		/// size_t with the target value, setting the size_t to the size of the Datum otherwise.
		/// </summary>
		/// <returns>A size_t indicating what index the target value was found at, set to the end of the Datum if not found.</returns>
		/// <param name ="value">Matrix4x4 value to be searched for within the Datum.</param>
		size_t Find(const glm::mat4& value) const;
		/// <summary>
		/// Searches for a RTTI* in the Datum with the provided value. Does not work if Datum is empty or Datum Type is not Pointer. If found, returns a
		/// size_t with the target value, setting the size_t to the size of the Datum otherwise.
		/// </summary>
		/// <returns>A size_t indicating what index the target value was found at, set to the end of the Datum if not found.</returns>
		/// <param name ="value">RTTI* value to be searched for within the Datum.</param>
		size_t Find(RTTI* value) const;

		//String functions
		/// <summary>
		/// Converts the Datum-held value at the provided index into a type-unique string variable, returning this string on completion. Does not work if the index is greater than or equal to
		/// the size of the Datum. Returns empty string "" on failure.
		/// <returns>An std::string representing the specified argument.</returns>
		/// <param name="index">The index of the target element in the Datum.</param>
		/// </summary>
		/// <returns>An std::string representing the specified argument.</returns>
		/// <param name="index">The index of the target element in the Datum.</param>
		std::string ToString(size_t index = 0) const;
		/// <summary>
		/// Accepts a string, then attempts to set a value at the specified index based on its value. On failure, false is returned. Does not work if the string represents a value of a type different
		/// from the Datum, or if the string is not formatted according to the specific data type's string representation format.
		/// </summary>
		/// <returns>A bool specifying whether the set succeeded.</returns>
		/// <param name="value">The char* corresponding to the user-provided.</param>
		/// <param name="index">The index of the target element in the Datum.</param>
		bool SetFromString(const char* value, size_t index = 0);

		bool IsExternalStorage();

	private:
		/// <summary>
		/// Sets external storage for the calling datum. Provided an array, the element type, and the number of elements for it to hold, the Datum will have external storage set to the array for the
		/// number of indicated elements. Does not work if the Datum already has elements stored internally or the type provided is not the same as the Datum's type.
		/// </summary>
		/// <param name="array">The array to be allocated for external storage.</param>
		/// <param name="size">The size for the external storage allocation.</param>
		/// <param name="type">The type of elements stored by the array.</param>
		void SetStorage(DatumTypes type, void* array, size_t size);
		void DeepCopy(const Datum& copiedDatum);

		/// <summary>
		/// A union representing the different types of variables that may be held by the Datum. After choosing a type, the type may not be changed for a Datum.
		/// </summary>
		union DatumValues final
		{
			size_t* i;
			float* f;
			std::string* s;
			glm::vec4* v;
			glm::mat4* m;
			RTTI** p;
			Scope** t;
			void* vp = nullptr;
		};

		/// <summary>
		/// The Datum itself, stores pointers to data types and can access its base address as well as any stored element.
		/// </summary>
		DatumValues Data;
		/// <summary>
		/// The current size of the Datum, the number of elements that it is currently storing. Always less than or equal to capacity.
		/// </summary>
		std::size_t CurrentSize{0};
		/// <summary>
		/// The current capacity of the Datum, the number of spaces it has reserved for elements of its type. Always greater than or equal to size.
		/// </summary>
		std::size_t CurrentCapacity{0};
		/// <summary>
		/// The type of elements held by the Datum, initialized to Unknown. Once set to a value besides Unknown, it can not be reassigned.
		/// </summary>
		DatumTypes DataType{ DatumTypes::Unknown };
		/// <summary>
		/// A boolean indicating whether or not the data is being stored externally. External storage means that the Datum has no control over the size or capacity of the container, and may not
		/// make any adjustments that change these values.
		/// </summary>
		bool IsExternal{ false };
		/// <summary>
		/// A lookup table indicating the sizes of each data type in bytes. Indices correspond to those assigned to the Data Type of the Datum.
		/// </summary>
		static constexpr size_t TypeSize[8] = {0, sizeof(size_t), sizeof(float), sizeof(std::string), sizeof(glm::vec4), sizeof(glm::mat4), sizeof(RTTI*), sizeof(Scope*)};
	};
};
//#include "Datum.cpp"