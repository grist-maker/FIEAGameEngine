#include "Datum.h"
/// <summary>
/// Defines functions declared for use with the Datum class.
/// </summary>
namespace FieaGameEngine
{
	//Base constructors
	Datum::Datum(DatumTypes type)
		:DataType{type}
	{
	}

	Datum::Datum(DatumTypes type, size_t size):
		DataType(type)
	{
		if (DataType != Datum::DatumTypes::Unknown)
		{
			Reserve(size); //Reserve throws an exception if the type is set to unknown, so it is unnecessary to check again here.
		}
	}

	//Scalar assignment operators
	Datum& Datum::operator=(const size_t newValue)
	{
		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Integer;
		}

		if (DataType != DatumTypes::Integer)
		{
			throw std::runtime_error("Cannot set Datum as equal to one with different type!");
		}

		if (CurrentSize > 0)
		{
			Clear();
		}

		PushBack(newValue);
		return *this;
	}

	Datum& Datum::operator=(const float newValue)
	{
		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Float;
		}

		if (DataType != DatumTypes::Float)
		{
			throw std::runtime_error("Cannot set Datum as equal to one with different type!");
		}

		if (CurrentSize > 0)
		{
			Clear();
		}

		PushBack(newValue);
		return *this;
	}

	Datum& Datum::operator=(const std::string& newValue)
	{
		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::String;
		}

		if (DataType != DatumTypes::String)
		{
			throw std::runtime_error("Cannot set Datum as equal to one with different type!");
		}

		if (CurrentSize > 0)
		{
			Clear();
		}

		PushBack(newValue);
		return *this;
	}

	Datum& Datum::operator=(const glm::vec4 newValue)
	{
		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Vector;
		}

		if (DataType != DatumTypes::Vector)
		{
			throw std::runtime_error("Cannot set Datum as equal to one with different type!");
		}

		if (CurrentSize > 0)
		{
			Clear();
		}

		PushBack(newValue);
		return *this;
	}

	Datum& Datum::operator=(const glm::mat4& newValue)
	{
		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Matrix;
		}

		if (DataType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Cannot set Datum as equal to one with different type!");
		}

		if (CurrentSize > 0)
		{
			Clear();
		}

		PushBack(newValue);
		return *this;
	}

	Datum& Datum::operator=(RTTI* newValue)
	{
		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Pointer;
		}

		if (DataType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Cannot set Datum as equal to one with different type!");
		}

		if (CurrentSize > 0)
		{
			Clear();
		}

		PushBack(newValue);
		return *this;
	}

	Scope& Datum::operator[](size_t index)
	{
		return *GetScope(index);
	}

	Scope& Datum::operator[](size_t index) const
	{
		return *GetConstScope(index);
	}

	//Move behavior
	Datum::Datum(Datum&& copiedDatum) noexcept:
	CurrentSize(copiedDatum.CurrentSize), CurrentCapacity(copiedDatum.CurrentCapacity), DataType(copiedDatum.DataType)//, IsExternal(copiedDatum.IsExternal)
	{
		if (copiedDatum.IsExternal)
		{
			SetStorage(DataType, copiedDatum.Data.vp, copiedDatum.Size());
		}
		else
		{
			Data.vp = copiedDatum.Data.vp;
		}

		copiedDatum.Data.vp = nullptr;
		copiedDatum.CurrentSize = 0;
		copiedDatum.CurrentCapacity = 0;
		copiedDatum.DataType = DatumTypes::Unknown;
	}

	Datum& Datum::operator=(Datum&& copiedDatum) noexcept
	{
		if (this != &copiedDatum && &copiedDatum.Data.vp != &Data.vp)
		{
			DataType = copiedDatum.DataType;
			if (!IsExternal)
			{
				Clear();
				ShrinkToFit();
				Data.vp = copiedDatum.Data.vp;
				CurrentSize = copiedDatum.CurrentSize;
				CurrentCapacity = copiedDatum.CurrentCapacity;
				IsExternal = copiedDatum.IsExternal;
			}
			else
			{
				SetStorage(DataType, copiedDatum.Data.vp, copiedDatum.Size());
			}

			copiedDatum.Data.vp = nullptr;
			copiedDatum.CurrentSize = 0;
			copiedDatum.CurrentCapacity = 0;
		}
		return *this;
	}
	
	//Typecast constructors
	Datum::Datum(size_t initialValue)
	{
		DataType = DatumTypes::Integer;
		PushBack(initialValue);
	}

	Datum::Datum(float initialValue)
	{
		DataType = DatumTypes::Float;
		PushBack(initialValue);
	}

	Datum::Datum(std::string& initialValue)
	{
		DataType = DatumTypes::String;
		PushBack(initialValue);
	}

	Datum::Datum(glm::vec4 initialValue)
	{
		DataType = DatumTypes::Vector;
		PushBack(initialValue);
	}

	Datum::Datum(glm::mat4& initialValue)
	{
		DataType = DatumTypes::Matrix;
		PushBack(initialValue);
	}

	Datum::Datum(RTTI* initialValue)
	{
		DataType = DatumTypes::Pointer;
		PushBack(initialValue);
	}

	Datum::Datum(Scope* initialValue)
	{
		DataType = DatumTypes::Table;
		PushBack(initialValue);
	}

	//Provided size typecast constructors
	Datum::Datum(size_t initialValue, size_t size)
	{
		DataType = DatumTypes::Integer;
		Reserve(size);
		PushBack(initialValue);
	}

	Datum::Datum(float initialValue, size_t size)
	{
		DataType = DatumTypes::Float;
		Reserve(size);
		PushBack(initialValue);
	}

	Datum::Datum(const std::string& initialValue, size_t size)
	{
		DataType = DatumTypes::String;
		Reserve(size);
		PushBack(initialValue);
	}

	Datum::Datum(glm::vec4 initialValue, size_t size)
	{
		DataType = DatumTypes::Vector;
		Reserve(size);
		PushBack(initialValue);
	}

	Datum::Datum(const glm::mat4& initialValue, size_t size)
	{
		DataType = DatumTypes::Matrix;
		Reserve(size);
		PushBack(initialValue);
	}

	Datum::Datum(RTTI* initialValue, size_t size)
	{
		DataType = DatumTypes::Pointer;
		Reserve(size);
		PushBack(initialValue);
	}

	//Datum copy constructor

	Datum::Datum(const Datum& copiedDatum)
	{
		DeepCopy(copiedDatum);
	}
	Datum& Datum::operator=(const Datum& copiedDatum)
	{
		if (this != &copiedDatum)
		{
			if (!IsExternal && CurrentCapacity > 0)
			{
				Clear();
				ShrinkToFit();
			}
			DeepCopy(copiedDatum);
		}
		return *this;
	}
	bool Datum::operator==(const Datum& comparedDatum) const
	{
		if (!(CurrentSize == comparedDatum.CurrentSize && DataType == comparedDatum.DataType && IsExternal == comparedDatum.IsExternal))
		{
			return false;
		}

		switch (DataType)
		{
		case FieaGameEngine::Datum::DatumTypes::Integer:
			for (size_t i = 0; i < CurrentSize; i++)
			{
				if (Data.i[i] != comparedDatum.Data.i[i])
				{
					return false;
				}
			}
			break;
		case FieaGameEngine::Datum::DatumTypes::Float:
			for (size_t i = 0; i < CurrentSize; i++)
			{
				if (Data.f[i] != comparedDatum.Data.f[i])
				{
					return false;
				}
			}
			break;
		case FieaGameEngine::Datum::DatumTypes::String:
			for (size_t i = 0; i < CurrentSize; i++)
			{
				if (Data.s[i] != comparedDatum.Data.s[i])
				{
					return false;
				}
			}
			break;
		case FieaGameEngine::Datum::DatumTypes::Vector:
			for (size_t i = 0; i < CurrentSize; i++)
			{
				if (Data.v[i] != comparedDatum.Data.v[i])
				{
					return false;
				}
			}
			break;
		case FieaGameEngine::Datum::DatumTypes::Matrix:
			for (size_t i = 0; i < CurrentSize; i++)
			{
				if (Data.m[i] != comparedDatum.Data.m[i])
				{
					return false;
				}
			}
			break;
		case FieaGameEngine::Datum::DatumTypes::Pointer:
			for (size_t i = 0; i < CurrentSize; i++)
			{
				if (Data.p[i] != nullptr)
				{
					if (!Data.p[i]->Equals(comparedDatum.Data.p[i]))
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	bool Datum::operator!=(const Datum& comparedDatum) const
	{
		return !(Datum::operator==(comparedDatum));
	}

	bool Datum::operator==(const size_t& comparedDatum) const
	{
		if (DataType != DatumTypes::Integer)
		{
			throw std::runtime_error("Cannot compare to scalar of different type!");
		}

		if (CurrentSize == 0)
		{
			throw std::runtime_error("Cannot compare empty datum!");
		}
		return (Data.i[0] == comparedDatum);
	}

	bool Datum::operator!=(const size_t& comparedDatum) const
	{
		return !(*this == comparedDatum);
	}

	bool Datum::operator==(const float& comparedDatum) const
	{
		if (DataType != DatumTypes::Float)
		{
			throw std::runtime_error("Cannot compare to scalar of different type!");
		}

		if (CurrentSize == 0)
		{
			throw std::runtime_error("Cannot compare empty datum!");
		}

		return (Data.f[0] == comparedDatum);
	}

	bool Datum::operator!=(const float& comparedDatum) const
	{
		return !(*this == comparedDatum);
	}

	bool Datum::operator==(const std::string& comparedDatum) const
	{
		if (DataType != DatumTypes::String)
		{
			throw std::runtime_error("Cannot compare to scalar of different type!");
		}

		if (CurrentSize == 0)
		{
			throw std::runtime_error("Cannot compare empty datum!");
		}

		return (Data.s[0] == comparedDatum);
	}

	bool Datum::operator!=(const std::string& comparedDatum) const
	{
		return !(*this == comparedDatum);
	}

	bool Datum::operator==(const glm::vec4& comparedDatum) const
	{
		if (DataType != DatumTypes::Vector)
		{
			throw std::runtime_error("Cannot compare to scalar of different type!");
		}

		if (CurrentSize == 0)
		{
			throw std::runtime_error("Cannot compare empty datum!");
		}

		return (Data.v[0] == comparedDatum);
	}

	bool Datum::operator!=(const glm::vec4& comparedDatum) const
	{
		return !(*this == comparedDatum);
	}

	bool Datum::operator==(const glm::mat4& comparedDatum) const
	{
		if (DataType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Cannot compare to scalar of different type!");
		}

		if (CurrentSize == 0)
		{
			throw std::runtime_error("Cannot compare empty datum!");
		}

		return (Data.m[0] == comparedDatum);
	}

	bool Datum::operator!=(const glm::mat4& comparedDatum) const
	{
		return !(*this == comparedDatum);
	}

	bool Datum::operator==(const RTTI* comparedDatum) const
	{
		if (DataType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Cannot compare to scalar of different type!");
		}

		if (CurrentSize == 0)
		{
			throw std::runtime_error("Cannot compare empty datum!");
		}
		if (Data.p[0] == nullptr)
		{
			return comparedDatum == nullptr;
		}
		return (Data.p[0]->Equals(comparedDatum));
	}

	bool Datum::operator!=(const RTTI* comparedDatum) const
	{
		return !(*this == comparedDatum);
	}

	//Datum destructor
	Datum::~Datum()
	{
		if (!IsExternal)
		{
			Clear();
			ShrinkToFit();
		}
	}

	Datum::DatumTypes Datum::Type() const
	{
		return DataType;
	}

	void Datum::SetType(DatumTypes type)
	{
		if (DataType == DatumTypes::Unknown)
		{
			DataType = type;
		}

		else if (DataType != type)
		{
			throw std::runtime_error("Cannot change type of data after it has already been assigned!");
		}
	}

	size_t Datum::Size() const
	{
		return CurrentSize;
	}

	size_t Datum::Capacity() const
	{
		return CurrentCapacity;
	}

	void Datum::Clear()
	{
		if (IsExternal)
		{
			throw std::runtime_error("Cannot remove values from External container!");
		}

		if (DataType == DatumTypes::String)
		{
			for (size_t i = 0; i < CurrentSize; i++)
			{
				Data.s[i].~basic_string();
			}
		}
		CurrentSize = 0;
	}

	void Datum::ShrinkToFit()
	{
		if (CurrentSize == 0 && !IsExternal && CurrentCapacity > 0)
		{
			free(Data.vp);
			Data.vp = nullptr;
			CurrentCapacity = 0;
		}

		if (CurrentCapacity > CurrentSize && !IsExternal)
		{
			void* data = nullptr;
			data = realloc(Data.vp, TypeSize[static_cast<size_t>(DataType)] * CurrentSize);
			assert(data != nullptr);
			Data.vp = data;
		}
	}

	//PushBack functions
	void Datum::PushBack(size_t newElement)
	{
		if (DataType != DatumTypes::Integer && DataType != DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot add object type that is not the same as the container's type!");
		}

		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Integer;
		}

		if (CurrentCapacity == CurrentSize)
		{
			if (IsExternal)
			{
				throw std::runtime_error("Cannot exceed size of external container!"); //Cannot push new value onto back since this memory is not owned by Datum
			}
			Reserve(CurrentCapacity + 1);
		}
		Data.i[CurrentSize] = newElement;
		CurrentSize++;
	}

	void Datum::PushBack(float newElement)
	{
		if (DataType != DatumTypes::Float && DataType != DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot add object type that is not the same as the container's type!");
		}

		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Float;
		}

		if (CurrentCapacity == CurrentSize)
		{
			if (IsExternal)
			{
				throw std::runtime_error("Cannot exceed size of external container!"); //Cannot push new value onto back since this memory is not owned by Datum
			}
			Reserve(CurrentCapacity + 1);
		}

		Data.f[CurrentSize] = newElement;
		CurrentSize++;
	}

	void Datum::PushBack(const std::string& newElement)
	{
		if (DataType != DatumTypes::String && DataType != DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot add object type that is not the same as the container's type!");
		}

		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::String;
		}

		if (CurrentCapacity == CurrentSize)
		{
			if (IsExternal)
			{
				throw std::runtime_error("Cannot exceed size of external container!"); //Cannot push new value onto back since this memory is not owned by Datum
			}
			Reserve(CurrentCapacity + 1);
		}
		
		new(Data.s + CurrentSize)std::string(newElement);
		CurrentSize++;
	}

	void Datum::PushBack(glm::vec4 newElement)
	{
		if (DataType != DatumTypes::Vector && DataType != DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot add object type that is not the same as the container's type!");
		}

		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Vector;
		}

		if (CurrentCapacity == CurrentSize)
		{
			if (IsExternal)
			{
				throw std::runtime_error("Cannot exceed size of external container!"); //Cannot push new value onto back since this memory is not owned by Datum
			}
			Reserve(CurrentCapacity + 1);
		}
		Data.v[CurrentSize] = newElement;
		CurrentSize++;
	}

	void Datum::PushBack(const glm::mat4& newElement)
	{
		if (DataType != DatumTypes::Matrix && DataType != DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot add object type that is not the same as the container's type!");
		}

		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Matrix;
		}

		if (CurrentCapacity == CurrentSize)
		{
			if (IsExternal)
			{
				throw std::runtime_error("Cannot exceed size of external container!"); //Cannot push new value onto back since this memory is not owned by Datum
			}
			Reserve(CurrentCapacity + 1);
		}
		Data.m[CurrentSize] = newElement;
		CurrentSize++;
	}

	void Datum::PushBack(RTTI* newElement)
	{
		if (DataType != DatumTypes::Pointer && DataType != DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot add object type that is not the same as the container's type!");
		}

		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Pointer;
		}

		if (CurrentCapacity == CurrentSize)
		{
			if (IsExternal)
			{
				throw std::runtime_error("Cannot exceed size of external container!"); //Cannot push new value onto back since this memory is not owned by Datum
			}
			Reserve(CurrentCapacity + 1);
		}
		Data.p[CurrentSize] = newElement;
		CurrentSize++;
	}

	void Datum::PushBack(Scope* newElement)
	{
		if (DataType != DatumTypes::Table && DataType != DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot add object type that is not the same as the container's type!");
		}

		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Table;
		}

		if (CurrentCapacity == CurrentSize)
		{
			if (IsExternal)
			{
				throw std::runtime_error("Cannot exceed size of external container!"); //Cannot push new value onto back since this memory is not owned by Datum
			}
			Reserve(CurrentCapacity + 1);
		}
		Data.t[CurrentSize] = &(*newElement);
		CurrentSize++;
	}

	void Datum::PopBack()
	{
		if (CurrentSize <= 0)
		{
			throw std::runtime_error("Cannot remove value from empty container!");
		}

		if (IsExternal)
		{
			throw std::runtime_error("Cannot remove values from External container!");
		}

		if (DataType == Datum::DatumTypes::String)
		{
			Data.s[CurrentSize-1].~basic_string();
		}
		CurrentSize--;
	}

	//SetStorage functions
	void Datum::SetStorage(size_t* elementArray, size_t elements)
	{
		SetStorage(DatumTypes::Integer, elementArray, elements);
	}

	void Datum::SetStorage(float* elementArray, size_t elements)
	{
		SetStorage(DatumTypes::Float, elementArray, elements);
	}

	void Datum::SetStorage(std::string* elementArray, size_t elements)
	{
		SetStorage(DatumTypes::String, elementArray, elements);
	}

	void Datum::SetStorage(glm::vec4* elementArray, size_t elements)
	{
		SetStorage(DatumTypes::Vector, elementArray, elements);
	}

	void Datum::SetStorage(glm::mat4* elementArray, size_t elements)
	{
		SetStorage(DatumTypes::Matrix, elementArray, elements);
	}

	void Datum::SetStorage(RTTI** elementArray, size_t elements)
	{
		SetStorage(DatumTypes::Pointer, elementArray, elements);
	}

	void Datum::SetStorage(DatumTypes type, void* array, size_t size)
	{
		if (DataType == DatumTypes::Unknown)
		{
			DataType = type;
		}

		else if (DataType != type)
		{
			throw std::runtime_error("Cannot change type of data after it has already been assigned!");
		}

		if (!IsExternal && CurrentCapacity > 0)
		{
			throw std::runtime_error("Cannot change to external storage after values have been assigned internally!");
		}

		if (IsExternal)
		{
			Data.vp = array;
			return;
		}

		IsExternal = true;
		Data.vp = array;
		CurrentSize = size;
		CurrentCapacity = size;
	}

	void Datum::Resize(size_t newSize)
	{
		if (IsExternal)
		{
			throw std::runtime_error("Cannot modify the size of externally managed data!");
		}

		if(DataType == DatumTypes::Unknown)
		{
			throw std::runtime_error("Type must be specified!");
		}

		if (newSize < 0 || newSize == CurrentCapacity)
		{
			return;
		}

		void* newData;

		if (CurrentCapacity > newSize && DataType == DatumTypes::String)// && DataType == DatumTypes::String) ///Clear the strings if they are populating it
		{
			for (size_t i = CurrentSize - 1; i >= newSize; i--)
			{
				(Data.s + i)->~basic_string();
			}
		}

		if (CurrentCapacity == 0)
		{
			newData = malloc(newSize * TypeSize[static_cast<size_t>(DataType)]);
			assert(newData != nullptr);
			Data.vp = newData;

			switch (DataType)
			{
			case FieaGameEngine::Datum::DatumTypes::String:
				for (size_t i = 0; i < newSize; i++)
				{
					new(Data.s + i)std::string();
				}
				break;
			default:
				memset(Data.vp, 0, newSize * TypeSize[static_cast<size_t>(DataType)]);
				break;
			}
		}

		else
		{
			newData = realloc(Data.vp, newSize * TypeSize[static_cast<size_t>(DataType)]);
			assert(newData != nullptr);
			Data.vp = newData;

			if (DataType == DatumTypes::String && CurrentCapacity < newSize)
			{
				for (size_t i = CurrentSize; i < newSize; i++)
				{
					new(Data.s + i)std::string();
				}
			}
		}
		CurrentSize = newSize;
		CurrentCapacity = newSize;
	}

	//Front functions
	size_t& Datum::FrontInt()
	{
		if (DataType != DatumTypes::Integer)
		{
			throw std::runtime_error("Cannot get integer value from a non-integer structure!");
		}
		return GetInt();
	}

	float& Datum::FrontFloat()
	{
		if (DataType != DatumTypes::Float)
		{
			throw std::runtime_error("Cannot get float value from a non-float structure!");
		}
		return GetFloat();
	}

	std::string& Datum::FrontString()
	{
		if (DataType != DatumTypes::String)
		{
			throw std::runtime_error("Cannot get string value from a non-string structure!");
		}
		return GetString();
	}

	glm::vec4& Datum::FrontVector()
	{
		if (DataType != DatumTypes::Vector)
		{
			throw std::runtime_error("Cannot get vector value from a non-vector structure!");
		}
		return GetVector();
	}

	glm::mat4& Datum::FrontMatrix()
	{
		if (DataType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Cannot get matrix value from a non-matrix structure!");
		}
		return GetMatrix();
	}

	RTTI*& Datum::FrontRTTI()
	{
		if (DataType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Cannot get RTTI value from a non-RTTI structure!");
		}
		return GetRTTI();
	}

	const size_t Datum::FrontConstInt() const
	{
		if (DataType != DatumTypes::Integer)
		{
			throw std::runtime_error("Cannot get integer value from a non-integer structure!");
		}
		return GetConstInt();
	}

	const float Datum::FrontConstFloat() const
	{
		if (DataType != DatumTypes::Float)
		{
			throw std::runtime_error("Cannot get float value from a non-float structure!");
		}
		return GetConstFloat();
	}

	const std::string& Datum::FrontConstString() const
	{
		if (DataType != DatumTypes::String)
		{
			throw std::runtime_error("Cannot get string value from a non-string structure!");
		}
		return GetConstString();
	}

	const glm::vec4 Datum::FrontConstVector() const
	{
		if (DataType != DatumTypes::Vector)
		{
			throw std::runtime_error("Cannot get vector value from a non-vector structure!");
		}
		return GetConstVector();
	}

	const glm::mat4 Datum::FrontConstMatrix() const
	{
		if (DataType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Cannot get matrix value from a non-matrix structure!");
		}
		return GetConstMatrix();
	}

	RTTI*const& Datum::FrontConstRTTI() const
	{
		if (DataType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Cannot get RTTI value from a non-RTTI structure!");
		}
		return GetConstRTTI();
	}

	size_t& Datum::BackInt()
	{
		if (CurrentSize <= 0)
		{
			throw std::runtime_error("Cannot access: the structure is empty!");
		}
		return GetInt(CurrentSize-1);
	}

	float& Datum::BackFloat()
	{
		if (CurrentSize <= 0)
		{
			throw std::runtime_error("Cannot access: the structure is empty!");
		}
		return GetFloat(CurrentSize - 1);
	}

	std::string& Datum::BackString()
	{
		if (CurrentSize <= 0)
		{
			throw std::runtime_error("Cannot access: the structure is empty!");
		}
		return GetString(CurrentSize - 1);
	}

	glm::mat4& Datum::BackMatrix()
	{
		if (CurrentSize <= 0)
		{
			throw std::runtime_error("Cannot access: the structure is empty!");
		}
		return GetMatrix(CurrentSize - 1);
	}

	glm::vec4& Datum::BackVector()
	{
		if (CurrentSize <= 0)
		{
			throw std::runtime_error("Cannot access: the structure is empty!");
		}
		return GetVector(CurrentSize - 1);
	}

	RTTI*& Datum::BackRTTI()
	{
		if (CurrentSize <= 0)
		{
			throw std::runtime_error("Cannot access: the structure is empty!");
		}
		return GetRTTI(CurrentSize - 1);
	}

	const size_t Datum::BackConstInt() const
	{
		if (CurrentSize <= 0)
		{
			throw std::runtime_error("Cannot access: the structure is empty!");
		}
		return GetConstInt(CurrentSize - 1);
	}

	const float Datum::BackConstFloat() const
	{
		if (CurrentSize <= 0)
		{
			throw std::runtime_error("Cannot access: the structure is empty!");
		}
		return GetConstFloat(CurrentSize - 1);
	}

	const std::string& Datum::BackConstString() const
	{
		if (CurrentSize <= 0)
		{
			throw std::runtime_error("Cannot access: the structure is empty!");
		}
		return GetConstString(CurrentSize - 1);
	}

	const glm::mat4& Datum::BackConstMatrix() const
	{
		if (CurrentSize <= 0)
		{
			throw std::runtime_error("Cannot access: the structure is empty!");
		}
		return GetConstMatrix(CurrentSize - 1);
	}

	const glm::vec4 Datum::BackConstVector() const
	{
		if (CurrentSize <= 0)
		{
			throw std::runtime_error("Cannot access: the structure is empty!");
		}
		return GetConstVector(CurrentSize - 1);
	}

	RTTI*const& Datum::BackConstRTTI() const
	{
		if (CurrentSize <= 0)
		{
			throw std::runtime_error("Cannot access: the structure is empty!");
		}
		return GetConstRTTI(CurrentSize - 1);
	}

	void Datum::SetInt(size_t value, size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Integer;
		}
		if (DataType != DatumTypes::Integer)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		Data.i[index] = value;
	}

	void Datum::SetFloat(float value, size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Float;
		}
		if (DataType != DatumTypes::Float)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		Data.f[index] = value;
	}

	void Datum::SetString(std::string& value, size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::String;
		}
		if (DataType != DatumTypes::String)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		Data.s[index] = value;
	}

	void Datum::SetVector(glm::vec4 value, size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Vector;
		}
		if (DataType != DatumTypes::Vector)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		Data.v[index] = value;
	}

	void Datum::SetMatrix(glm::mat4& value, size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Matrix;
		}
		if (DataType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		Data.m[index] = value;
	}

	void Datum::SetRTTI(RTTI* value, size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Pointer;
		}
		if (DataType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		Data.p[index] = value;
	}

	void Datum::SetScope(Scope* value, size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType == DatumTypes::Unknown)
		{
			DataType = DatumTypes::Table;
		}
		if (DataType != DatumTypes::Table)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		Data.t[index] = value;
	}

	size_t& Datum::GetInt(size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::Integer)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		return Data.i[index];
	}

	float& Datum::GetFloat(size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::Float)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		return Data.f[index];
	}

	std::string& Datum::GetString(size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::String)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		return Data.s[index];
	}

	glm::vec4& Datum::GetVector(size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::Vector)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		return Data.v[index];
	}

	glm::mat4& Datum::GetMatrix(size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		return Data.m[index];
	}

	RTTI*& Datum::GetRTTI(size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		return Data.p[index];
	}

	Scope*& Datum::GetScope(size_t index)
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::Table)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		return Data.t[index];
	}

	const size_t Datum::GetConstInt(size_t index) const
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::Integer)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		const size_t newValue = Data.i[index];
		return newValue;
	}

	const float Datum::GetConstFloat(size_t index) const
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::Float)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		const float newValue = Data.f[index];
		return newValue;
	}

	const std::string& Datum::GetConstString(size_t index) const
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::String)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		const std::string& newValue = Data.s[index];
		return newValue;
	}

	const glm::vec4 Datum::GetConstVector(size_t index) const
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::Vector)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		const glm::vec4 newValue = Data.v[index];
		return newValue;
	}

	const glm::mat4& Datum::GetConstMatrix(size_t index) const
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		const glm::mat4& newValue = Data.m[index];
		return 	newValue;
	}

	RTTI*const& Datum::GetConstRTTI(size_t index) const
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		return Data.p[index];
	}

	Scope*const& Datum::GetConstScope(size_t index) const
	{
		if (index >= CurrentSize)
		{
			throw std::runtime_error("Cannot set value at index that exceeds array size!");
		}
		if (DataType != DatumTypes::Table)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}
		return Data.t[index];
	}

	size_t Datum::Find(const size_t value) const
	{
		if (DataType != DatumTypes::Integer)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}

		for (size_t position = 0; position < CurrentSize; ++position)
		{
			if (Data.i[position] == value)
			{
				return position;
			}
		}
		return CurrentSize;
	}

	size_t Datum::Find(const float value) const
	{
		if (DataType != DatumTypes::Float)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}

		for (size_t position = 0; position < CurrentSize; ++position)
		{
			if (Data.f[position] == value)
			{
				return position;
			}
		}
		return CurrentSize;
	}

	void Datum::Reserve(size_t size)
	{
		if (size <= CurrentCapacity)
		{
			return;
		}

		if (IsExternal)
		{
			throw std::runtime_error("Cannot reserve values for external datum!");
		}

		if (DataType == DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot reserve space for unknown type!");
		}

		void* newData;
		if (CurrentCapacity == 0)
		{
			newData = malloc(size * TypeSize[static_cast<size_t>(DataType)]);
		}
		else
		{
			newData = realloc(Data.vp, size * TypeSize[static_cast<size_t>(DataType)]);
		}
		assert(newData != nullptr);
		Data.vp = newData;
		CurrentCapacity = size;
	}

	size_t Datum::Find(const std::string& value) const
	{
		if (DataType != DatumTypes::String)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}

		for (size_t position = 0; position < CurrentSize; ++position)
		{
			if (Data.s[position] == value)
			{
				return position;
			}
		}
		return CurrentSize;
	}

	size_t Datum::Find(const glm::vec4 value) const
	{
		if (DataType != DatumTypes::Vector)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}

		for (size_t position = 0; position < CurrentSize; ++position)
		{
			if (Data.v[position] == value)
			{
				return position;
			}
		}
		return CurrentSize;
	}

	size_t Datum::Find(const glm::mat4& value) const
	{
		if (DataType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}

		for (size_t position = 0; position < CurrentSize; ++position)
		{
			if (Data.m[position] == value)
			{
				return position;
			}
		}
		return CurrentSize;
	}

	size_t Datum::Find(RTTI* value) const
	{
		if (DataType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Cannot access value of type that differs from that of the Datum!");
		}

		for (size_t position = 0; position < CurrentSize; ++position)
		{
			if (Data.p[position]->Equals(value))
			{
				return position;
			}
		}
		return CurrentSize;
	}

	bool Datum::Remove(size_t value)
	{
		if (DataType != DatumTypes::Integer)
		{
			throw std::runtime_error("Cannot remove value of type that differs from that of the Datum!");
		}
		return (RemoveAt(Find(value)));
	}
	bool Datum::Remove(float value)
	{
		if (DataType != DatumTypes::Float)
		{
			throw std::runtime_error("Cannot remove value of type that differs from that of the Datum!");
		}
		return (RemoveAt(Find(value)));
	}
	bool Datum::Remove(const std::string& value)
	{
		if (DataType != DatumTypes::String)
		{
			throw std::runtime_error("Cannot remove value of type that differs from that of the Datum!");
		}
		return (RemoveAt(Find(value)));
	}
	bool Datum::Remove(glm::vec4 value)
	{
		if (DataType != DatumTypes::Vector)
		{
			throw std::runtime_error("Cannot remove value of type that differs from that of the Datum!");
		}
		return (RemoveAt(Find(value)));
	}
	bool Datum::Remove(const glm::mat4& value)
	{
		if (DataType != DatumTypes::Matrix)
		{
			throw std::runtime_error("Cannot remove value of type that differs from that of the Datum!");
		}
		return (RemoveAt(Find(value)));
	}
	bool Datum::Remove(RTTI* value)
	{
		if (DataType != DatumTypes::Pointer)
		{
			throw std::runtime_error("Cannot remove value of type that differs from that of the Datum!");
		}
		return (RemoveAt(Find(value)));
	}

	bool Datum::RemoveAt(size_t index)
	{
		if (index >= CurrentSize)
		{
			return false;
		}
		if (DataType == Datum::DatumTypes::String)
		{
			(Data.s + index)->~basic_string();
		}
		memmove(static_cast<std::byte*>(Data.vp) + (index * TypeSize[static_cast<size_t>(DataType)]), static_cast<std::byte*>(Data.vp) + ((index + 1) * TypeSize[static_cast<size_t>(DataType)]), (CurrentSize - index) * TypeSize[static_cast<size_t>(DataType)]);
		CurrentSize--;
		return true;
	}

	std::string Datum::ToString(size_t index) const
	{
		if (DataType == DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot convert typeless element to string!");
		}

		if (index < CurrentSize)
		{
			switch (DataType)
			{
			case FieaGameEngine::Datum::DatumTypes::Integer:
				return std::to_string(GetConstInt(index));
			case FieaGameEngine::Datum::DatumTypes::Float:
				return std::to_string(GetConstFloat(index));
			case FieaGameEngine::Datum::DatumTypes::String:
				return GetConstString(index);
			case FieaGameEngine::Datum::DatumTypes::Vector:
				return glm::to_string(GetConstVector(index));
			case FieaGameEngine::Datum::DatumTypes::Matrix:
				return glm::to_string(GetConstMatrix(index));
			case FieaGameEngine::Datum::DatumTypes::Pointer:
				return GetConstRTTI(index)->ToString();
			}
		}
		return "";
	}

	bool Datum::SetFromString(const char* value, size_t index)
	{
		if (DataType == DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot convert typeless element to string!");
		}
		if (index < CurrentSize && value != nullptr)
		{
			std::string stringValue = value;
			switch (DataType)
			{
			case FieaGameEngine::Datum::DatumTypes::Integer:
				if (sscanf_s(value, "%u", reinterpret_cast<int32_t*>(& Data.i[index])) == static_cast<size_t>(1))
				{
					return true;
				}
				break;

			case FieaGameEngine::Datum::DatumTypes::Float:
				if (sscanf_s(value, "%f", &Data.f[index]) == 1)
				{
					return true;
				}
				break;
			case FieaGameEngine::Datum::DatumTypes::String:
					SetString(stringValue, index);
					return true;
				break;
			case FieaGameEngine::Datum::DatumTypes::Vector:
				if (sscanf_s(value, "vec4(%f, %f, %f, %f)", &Data.v[index].x, &Data.v[index].y, &Data.v[index].z, &Data.v[index].w) == 4)
				{
					return true;
				}
				break;
			case FieaGameEngine::Datum::DatumTypes::Matrix:
				if (sscanf_s(value, "mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", &Data.m[index][0][0], &Data.m[index][0][1], &Data.m[index][0][2], &Data.m[index][0][3],
					&Data.m[index][1][0], &Data.m[index][1][1], &Data.m[index][1][2], &Data.m[index][1][3],
					&Data.m[index][2][0], &Data.m[index][2][1], &Data.m[index][2][2], &Data.m[index][2][3],
					&Data.m[index][3][0], &Data.m[index][3][1], &Data.m[index][3][2], &Data.m[index][3][3]) == 16)
				{
					return true;
				}
				break;
			}
		}
		return false;
	}

	void Datum::DeepCopy(const Datum& copiedDatum)
	{
		IsExternal = copiedDatum.IsExternal;
		DataType = copiedDatum.DataType;
		CurrentCapacity = 0;
		CurrentSize = 0;

		if (copiedDatum.IsExternal) //Needs shallow copy
		{
			CurrentCapacity = copiedDatum.CurrentCapacity;
			CurrentSize = copiedDatum.CurrentSize;
			Data.vp = copiedDatum.Data.vp;
		}
		else //Needs deep copy
		{
			switch (DataType)
			{
			case(DatumTypes::String):
				for (size_t i = 0; i < copiedDatum.CurrentSize; i++)
				{
					PushBack(copiedDatum.Data.s[i]);
				}
				break;

			case(DatumTypes::Table):
				break;

			default:
				Reserve(copiedDatum.Size());
				memcpy(Data.vp, copiedDatum.Data.vp, TypeSize[static_cast<size_t>(DataType)] * copiedDatum.CurrentSize);
				CurrentSize = copiedDatum.CurrentSize;
			}
		}
	}

	bool Datum::IsExternalStorage()
	{
		return IsExternal;
	}
};