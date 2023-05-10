#pragma once
#include <cstddef>
#include <string>

/// <summary>
/// Declares the RTTI class, used to allow objects of a variety of different types to be operated on and stored in a similar way.
/// </summary>
namespace FieaGameEngine
{
	class RTTI
	{
	public:
		using IdType = std::size_t;

		RTTI() = default;
		RTTI(const RTTI&) = default;
		RTTI& operator=(const RTTI&) = default;
		RTTI(RTTI&&) noexcept = default;
		RTTI& operator=(RTTI&&) noexcept = default;
		virtual ~RTTI() = default;

		virtual [[nodiscard]] IdType TypeIdInstance() const = 0;
		virtual [[nodiscard]] bool Is(IdType) const;

		template <typename T>
		T* As();

		template <typename T>
		const T* As() const;

		virtual std::string ToString() const
		{
			using namespace std::string_literals;
			return "RTTI"s;
		}

		virtual bool Equals(const RTTI* rhs) const
		{
			return this == rhs;
		}
	};
}

#define RTTI_DECLARATIONS(Type, ParentType)																					\
	public:																													\
		static FieaGameEngine::RTTI::IdType TypeIdClass() { return _typeId; }												\
		FieaGameEngine::RTTI::IdType TypeIdInstance() const override { return TypeIdClass(); }								\
		bool Is(FieaGameEngine::RTTI::IdType id) const override { return (id == _typeId ? true : ParentType::Is(id)); }		\
	private:																												\
		static const FieaGameEngine::RTTI::IdType _typeId																	\
																															
#define RTTI_DEFINITIONS(Type)																								\
	const FieaGameEngine::RTTI::IdType Type::_typeId = reinterpret_cast<FieaGameEngine::RTTI::IdType>(&Type::_typeId)		\
	

#include "RTTI.inl"