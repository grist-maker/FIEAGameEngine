#include "RTTI.h"
/// <summary>
/// Used to define inline functions of the RTTI class.
/// </summary>
namespace FieaGameEngine
{
	inline bool RTTI::Is(IdType) const
	{
		return false;
	}

	template <typename T>
	inline const T* RTTI::As() const
	{
		return (Is(T::TypeIdClass()) ? reinterpret_cast<const T*>(this) : nullptr);
	}

	template <typename T>
	inline T* RTTI::As()
	{
		return (Is(T::TypeIdClass()) ? reinterpret_cast<T*>(const_cast<RTTI*>(this)) : nullptr);
	} 
}
