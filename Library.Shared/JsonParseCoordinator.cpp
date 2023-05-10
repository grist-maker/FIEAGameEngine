#include "JsonParseCoordinator.h"
#include "IJsonParseHelper.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(JsonParseCoordinator::Wrapper);
	std::shared_ptr<JsonParseCoordinator::Wrapper> JsonParseCoordinator::Wrapper::Create() const
	{
		std::shared_ptr<JsonParseCoordinator::Wrapper> newWrapper;
		return newWrapper;
	}

	void JsonParseCoordinator::Wrapper::Initialize()
	{

	}
	void JsonParseCoordinator::Wrapper::SetJsonParseCoordinator(JsonParseCoordinator* address)
	{
		CoordinatorAddress = address;
	}

	JsonParseCoordinator* JsonParseCoordinator::Wrapper::GetJsonParseCoordinator()
	{
		return CoordinatorAddress;
	}

	void JsonParseCoordinator::Wrapper::IncrementDepth()
	{
		if (CurrentDepth < 65535)
		{
			++CurrentDepth;
		}
	}

	void JsonParseCoordinator::Wrapper::DecrementDepth()
	{
		if (CurrentDepth != 0)
		{
			--CurrentDepth;
		}
	}

	size_t JsonParseCoordinator::Wrapper::Depth() const
	{
		return CurrentDepth;
	}

	JsonParseCoordinator::JsonParseCoordinator(std::shared_ptr<Wrapper> wrapper)
		:ContainedWrapper(move(wrapper))
	{
		ContainedWrapper->SetJsonParseCoordinator(this);
	}

	JsonParseCoordinator::JsonParseCoordinator(JsonParseCoordinator&& movedCoordinator) noexcept
	{
		SetWrapper(movedCoordinator.GetWrapper());
		Helpers = std::move(movedCoordinator.Helpers);
	}

	JsonParseCoordinator& JsonParseCoordinator::operator=(JsonParseCoordinator&& movedCoordinator) noexcept
	{
		if (&movedCoordinator != this)
		{
			Helpers.Clear();
			SetWrapper(movedCoordinator.GetWrapper());
			Helpers = std::move(movedCoordinator.Helpers);
		}
		return *this;
	}

	std::unique_ptr<JsonParseCoordinator> JsonParseCoordinator::Clone()
	{
		std::shared_ptr<JsonParseCoordinator::Wrapper> cloneWrapper(GetWrapper()->Create());
		std::unique_ptr<JsonParseCoordinator> cloneCoordinator(new JsonParseCoordinator(cloneWrapper));

		for (size_t i = 0; i < Helpers.Size(); i++)
		{
			cloneCoordinator->AddHelper(Helpers[i]->Create());
		}
		return cloneCoordinator;
	}

	void JsonParseCoordinator::AddHelper(std::shared_ptr<IJsonParseHelper> newHelper)
	{
		for (size_t i = 0; i < Helpers.Size(); i++)
		{
			if (newHelper->TypeIdInstance() == Helpers[i]->TypeIdInstance())
			{
				throw std::runtime_error("Cannot add existing element!");
			}
		}
		Helpers.PushBack(newHelper);
	}

	void JsonParseCoordinator::RemoveHelper(std::shared_ptr<IJsonParseHelper> removedHelper)
	{
		RemoveHelper(removedHelper->TypeIdInstance());
	}

	void JsonParseCoordinator::RemoveHelper(RTTI::IdType HelperId)
	{
		for (size_t i = 0; i < Helpers.Size(); i++)
		{
			if (HelperId== Helpers[i]->TypeIdInstance())
			{
				Helpers.Remove(Helpers[i]);
				break;
			}
		}
	}

	size_t JsonParseCoordinator::HelperSize()
	{
		return Helpers.Size();
	}

	const Vector<std::shared_ptr<IJsonParseHelper>>& JsonParseCoordinator::HelperList()
	{
		return Helpers;
	}

	void JsonParseCoordinator::DeserializeObject(const std::string& JSONData)
	{
		std::istringstream inputStream(JSONData);
		DeserializeObject(inputStream);
	}

	void JsonParseCoordinator::DeserializeObjectFromFile(const std::string& fileName)
	{
		std::ifstream file{ fileName };
		std::stringstream stringBuffer;

		if (!file.good())
		{
			throw std::runtime_error("Cannot open file!");
		}
		stringBuffer << file.rdbuf();
		DeserializeObject(stringBuffer);
		file.close();
	}

	void JsonParseCoordinator::DeserializeObject(std::istream& JSONData)
	{
		Json::Value foundValue;
		JSONData >> foundValue;

		GetWrapper()->IncrementDepth();
		Initialize();
		ParseMembers(foundValue);
		if (GetWrapper()->Depth() > 0)
		{
			GetWrapper()->DecrementDepth();
		}
	}

	std::shared_ptr<JsonParseCoordinator::Wrapper> JsonParseCoordinator::GetWrapper()
	{
		return ContainedWrapper;
	}

	void JsonParseCoordinator::SetWrapper(std::shared_ptr<Wrapper> wrapperAddress)
	{
		if (GetWrapper() != nullptr)
		{
			GetWrapper()->SetJsonParseCoordinator(nullptr);
		}
		ContainedWrapper = wrapperAddress;
	}

	void JsonParseCoordinator::ParseMembers(const Json::Value& object)
	{
		auto allMembers = object.getMemberNames();

		for (size_t i = 0; i < allMembers.size(); i++)
		{
			if (object[allMembers[i]].isObject() && object[allMembers[i]].getMemberNames() != Json::Value::Members())
			{
				GetWrapper()->IncrementDepth();
				Parse(allMembers[i], object[allMembers[i]]);
			}
			else
			{
				Parse(allMembers[i], object[allMembers[i]]);
			}
		}
	}

	void JsonParseCoordinator::Parse(const std::string& valueString, const Json::Value& value)
	{
		for (size_t i = 0; i < Helpers.Size(); i++)
		{
			bool isArray;
			if (Helpers[i]->StartHandler(*ContainedWrapper, std::pair<const std::string&, const Json::Value&>(valueString, value), isArray))
			{
				if (value["Value"].isObject() || (value["Value"].isArray() && value["Value"][0].isObject())) //Is this a nested scope?
				{
					if (isArray)
					{
						for (size_t j = 0; j < value["Value"].size(); j++)
						{
							ParseMembers(value["Value"][static_cast<Json::Value::ArrayIndex>(j)]);
						}
					}
					else
					{
						ParseMembers(value["Value"]);
					}
				}
				Helpers[i]->EndHandler(*ContainedWrapper, std::pair<const std::string&, const Json::Value&>(valueString, value), isArray);
				i = Helpers.Size();
			}
		}
		if (value.isObject() && ContainedWrapper->Depth() != 0)
		{
			ContainedWrapper->DecrementDepth();
		}
	}

	void JsonParseCoordinator::Initialize()
	{
		for (size_t i = 0; i < Helpers.Size(); i++)
		{
			Helpers[i]->Initialize();
		}
	}
}