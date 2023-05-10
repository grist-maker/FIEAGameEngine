#pragma once
#include "pch.h"
#include "HashMap.h"
#include <cassert>
#include "RTTI.h"
#include "Datum.h"
#include "Vector.h"
#include "json/json.h"
#include "JsonParseCoordinator.h"

namespace FieaGameEngine
{
	/// <summary>
	/// The IJsonParseHelper class, providing an interface the JSONParseCoordinator may use to interact with derived helper objects. These helpers have knowledge of JSON grammar
	/// and traversal as defined by the user, and use this to traverse a parsed JSON value for content to transcribe into user-accessible objects, like Scopes and data
	/// primitives. This is versatile, and can be readily extended as needed to produce different helpers. It is an RTTI, ensuring that two helpers of the same type will not
	/// end up in a Helpers list, as such is inefficient and a waste of memory and time, since all helpers of the same type can parse the same data.
	/// </summary>
	class IJsonParseHelper : RTTI
	{
		RTTI_DECLARATIONS(IJsonParseHelper, RTTI);
	public:
		virtual ~IJsonParseHelper() = default;
		/// <summary>
		/// Initializes the Helper as necessary to prepare it for parsing a fresh JSON stream of data.
		/// </summary>
		virtual void Initialize();

		/// <summary>
		/// The StartHandler function, called when a Helper attempts to parse JSON data. After performing necessary logical checks and attempting a parse if successful, it returns a boolean indicating whether or not
		/// the parse succeeded. If successful, the EndHandler function should be called by the Parse Coordinator.
		/// </summary>
		/// <param name="targetWrapper">The wrapper that the Helper works with to parse JSON data. If the two are compatible and the parse succeeds, parsed data may be stored inside the wrapper.</param>
		/// <param name="value">The string JSON::value pair that will be checked to be parsed.</param>
		/// <param name="isArray">Whether or not the values are stored in an array format.</param>
		/// <returns>Indicates whether or not the helper was able to parse the target data.</returns>
		virtual bool StartHandler(JsonParseCoordinator::Wrapper& coordinator, const std::pair<const std::string, Json::Value>& value, bool& isArray) = 0;
		/// <summary>
		/// The EndHandler function, called when the helper's checks made in StartHandler all succeed. The EndHandler function primarily serves to wrap up any loose ends left after a successful parse. It is overriden
		/// by different helpers based on needs and operation to perform differently based on the situation
		/// </summary>
		/// <param name="targetWrapper">The wrapper that the Helper will transer parsed JSON data to.</param>
		/// <param name="value">The string JSON::value pair that has been parsed.</param>
		/// <param name="isArray">Whether or not the Json::Value stores an array of values.</param>
		virtual void EndHandler(JsonParseCoordinator::Wrapper& coordinator, const std::pair<const std::string, Json::Value>& value, bool& isArray) = 0;

		/// <summary>
		/// A virtual function that is used to effectively "Clone" the calling helper. This actually creates an entirely new Helper object, ensuring that its the same derived class as the calling helper,
		/// wth the same capabilities, but without any helper stored data. This lets the original helper and its clone, now separate, be used in tandem by two concurrent parsing operations with a
		/// single function call.
		/// </summary>
		/// <returns>A shared_ptr to the newly constructed helper, ready for use by the new owner.</returns>
		virtual std::shared_ptr<IJsonParseHelper> Create() const = 0;

		/// <summary>
		/// Used to "clean" the helper following its use in a parsing operation. This cleans any residual, unnecessary data that may have been set in the Initialize call or subsequent parsing activity. It
		/// is virtual and can be tailored by derived classes as necessary to suit the helper's specification.
		/// </summary>
		virtual void Cleanup();
	};
}