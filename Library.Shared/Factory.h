#pragma once
#include "HashMap.h"
#include <string>

namespace FieaGameEngine
{
	/// <summary>
	/// The factory class, an abstract base class that provides a pattern for derived classes to follow. The factory pattern is used to allow
	/// the creation of objects based on their class name as specified via string or JSON text, allowing ease of use and readability in code when creating games and large applications.
	/// It support file input for relevant game data.
	/// </summary>
	template <typename T>
	class Factory
	{
	public:
		/// <summary>
		/// The default Factory constructor. No special work needs to be done, so its definition is defaulted.
		/// </summary>
		Factory() = default;
		/// <summary>
		/// The virtual Factory destructor. No special work needs to be done in the base class, so its definition is defaulted but allows for extendability by derived classes that need
		/// changes to it to function properly.
		/// </summary>
		virtual ~Factory() = default;

		/// <summary>
		/// Allows the user to add a new supported concrete Factory type to the list of supported factories. This lets the abstract factory
		/// support the creation of the specified concrete type.
		/// </summary>
		/// <param name="newFactory">A unique pointer to the concrete factory to be added to the supported factory list.</param>
		static void Add(std::unique_ptr<const Factory> newFactory);

		/// <summary>
		/// Allows the user to remove a concrete factory type contained in the list of supported factories. This means that the abstract factory
		/// will no longer support the creation of this concrete type.
		/// </summary>
		/// <param name="targetFactory">The name of the object created by the concrete factory to be removed from the supported factory list.</param>
		static void Remove(const std::string& targetFactory);

		/// <summary>
		/// Allows a user to retrieve a pointer to a concrete factory by providing the name of the class as an argument. It will search through its supported
		/// ConcreteFactories HashMap, returning it if found, or nullptr if not.
		/// </summary>
		/// <returns>A pointer to the found concrete factory.</returns>
		/// <param name="className">The name of the object class instantiated by the concrete factory type being searched for.</param>
		static const Factory<T>* Find(const std::string& className);
		/// <summary>
		/// Creates an object of the class with the name specified in the string argument className, then returning this object for the user
		/// to access and use as desired. This may be invoked by an abstract factory that has references to concrete derived factories.
		/// </summary>
		/// <param name="className">The name of the class that should be instantiated.</param>
		/// <returns>A gsl owner of a pointer to an instance of the class with the name provided via string.</returns>
		[[nodiscard]] static gsl::owner<T*> Create(const std::string& className);
		/// <summary>
		/// Invoked by concrete derived factories. Creates a new object of the class that the concrete factory is associated with, then returning a gsl owner of a pointer of this
		/// new object to the user.
		/// </summary>
		/// <returns>A gsl owner to a pointer to an object created by the calling factory.</returns>
		[[nodiscard]] virtual gsl::owner<T*> Create() const = 0;
		/// <summary>
		/// Returns the name of the class that the calling Factory is able to create instances of. This is a pure virtual function that may differ in
		/// operation based on the calling type.
		/// </summary>
		/// <returns>A string indicating the name of the class that the factory can create instances of.</returns>
		virtual const std::string& ClassName() const = 0;

	private:
		/// <summary>
		/// The hashmap that holds string& std::unique_ptr<Factory> pairs. The string represents the name of the class created by the Factory to which it is paired with. Each
		/// of these strings specifies a class type that the abstract Factory is capable of asking the paired concrete Factory to create associated class instances of.
		/// </summary>
		inline static HashMap<std::string, std::unique_ptr<const Factory>> Factories;
	};

	/// <summary>
	/// The ConcreteFactory macro, used to automate the creation of derived factory classes provided the name of the concrete and abstract product type. This version is intended for use
	/// by classes that are defined in the FieaGameEngine namespace, that is, classes that are not created strictly for testing.
	/// </summary>

	#define ConcreteFactory(ConcreteProductType, AbstractProductType) \
	class ConcreteProductType## Factory : public FieaGameEngine::Factory<AbstractProductType>\
	{ \
	public:\
		AbstractProductType* Create() const override \
		{\
			AbstractProductType* newMember = new ConcreteProductType();\
			return newMember; \
		}\
		const std::string& ClassName() const override\
		{\
			return typeName;\
		}\
		const std::string typeName = #ConcreteProductType;\
	};
}
#include "Factory.inl"