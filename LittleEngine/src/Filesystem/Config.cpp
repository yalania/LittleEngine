#include "Config.h"

#include "Filesystem/File.h"
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

Config::Config()
{
	configDocument.SetObject();
	allocator = &configDocument.GetAllocator();
}

Config::Config(const std::vector<char>& data)
{
	std::string serialized_string(data.front(), data.size());
	configDocument.Parse(serialized_string.c_str());
	allocator = &configDocument.GetAllocator();
}

Config::Config(const rapidjson::Value& object_value)
{
	configDocument.CopyFrom(object_value, configDocument.GetAllocator());
}

Config::Config(const std::string& serialized_scene_string)
{
	configDocument.Parse(serialized_scene_string.c_str());
	allocator = &configDocument.GetAllocator();
}

Config::Config(const Config& other)
{
	configDocument.CopyFrom(other.configDocument, configDocument.GetAllocator());
	allocator = &configDocument.GetAllocator();
}

Config& Config::operator=(const Config& other)
{
	configDocument.CopyFrom(other.configDocument, configDocument.GetAllocator());
	allocator = &configDocument.GetAllocator();
	return *this;
}

rapidjson::Document::AllocatorType& Config::GetAllocator() const
{
	return *allocator;
}

void Config::AddInt(int valueToAdd, const std::string &name)
{
	rapidjson::Value member_name(name.c_str(), *allocator);
	configDocument.AddMember(member_name, valueToAdd, *allocator);
}

int Config::GetInt(const std::string& name, int optValue) const
{
	if (!configDocument.HasMember(name.c_str()))
	{
		return optValue;
	}
	else
	{
		const rapidjson::Value& current_value = configDocument[name.c_str()];
		return current_value.GetInt();
	}
}

void Config::AddUInt(uint64_t valueToAdd, const std::string& name)
{
	rapidjson::Value member_name(name.c_str(), *allocator);
	configDocument.AddMember(member_name, valueToAdd, *allocator);
}

uint64_t Config::GetUInt(const std::string& name, unsigned int optValue) const
{
	if (!configDocument.HasMember(name.c_str()))
	{
		return optValue;
	}
	else
	{
		const rapidjson::Value& current_value = configDocument[name.c_str()];
		return current_value.GetUint64();
	}
}
void Config::AddUInt32(uint32_t valueToAdd, const std::string & name)
{
	rapidjson::Value member_name(name.c_str(), *allocator);
	configDocument.AddMember(member_name, valueToAdd, *allocator);
}
uint32_t Config::GetUInt32(const std::string & name, unsigned int optValue) const
{
	if (!configDocument.HasMember(name.c_str()))
	{
		return optValue;
	}
	else
	{
		const rapidjson::Value& current_value = configDocument[name.c_str()];
		return current_value.GetUint();
	}
}
void Config::AddInt64(int64_t valueToAdd, const std::string& name)
{
	rapidjson::Value member_name(name.c_str(), *allocator);
	configDocument.AddMember(member_name, valueToAdd, *allocator);
}

int64_t Config::GetInt64(const std::string& name, int64_t optValue) const
{
	if (!configDocument.HasMember(name.c_str()))
	{
		return optValue;
	}
	else
	{
		const rapidjson::Value& current_value = configDocument[name.c_str()];
		return current_value.GetInt64();
	}
}
void Config::AddFloat(float valueToAdd, const std::string& name)
{
	rapidjson::Value member_name(name.c_str(), *allocator);
	configDocument.AddMember(member_name, valueToAdd, *allocator);
}

float Config::GetFloat(const std::string& name, float optValue) const
{
	if (!configDocument.HasMember(name.c_str()))
	{
		return optValue;
	}
	else
	{
		const rapidjson::Value& current_value = configDocument[name.c_str()];
		return current_value.GetFloat();
	}
}

void Config::AddBool(bool valueToAdd, const std::string& name)
{
	rapidjson::Value member_name(name.c_str(), *allocator);
	configDocument.AddMember(member_name, valueToAdd, *allocator);
}

bool Config::GetBool(const std::string& name, bool optValue) const
{
	if (!configDocument.HasMember(name.c_str()))
	{
		return optValue;
	}
	else
	{
		const rapidjson::Value& current_value = configDocument[name.c_str()];
		return current_value.GetBool();
	}
}

void Config::AddString(const std::string valueToAdd, const std::string& name)
{
	rapidjson::Value member_name(name.c_str(), *allocator);
	rapidjson::Value string_value(valueToAdd.c_str(), valueToAdd.size(), *allocator);
	configDocument.AddMember(member_name, string_value, *allocator);
}

void Config::GetString(const std::string& name, std::string& returnValue, const std::string& optValue) const
{
	if (!configDocument.HasMember(name.c_str()))
	{
		returnValue = optValue;
	}
	else
	{
		const rapidjson::Value& current_value = configDocument[name.c_str()];
		returnValue = std::string(current_value.GetString(), current_value.GetStringLength());
	}
}

void Config::AddFloat3(const glm::vec3& valueToAdd, const std::string& name)
{
	rapidjson::Value member_name(name.c_str(), *allocator);
	rapidjson::Value array_value(rapidjson::kArrayType);
	array_value.PushBack(valueToAdd.x, *allocator);
	array_value.PushBack(valueToAdd.y, *allocator);
	array_value.PushBack(valueToAdd.z, *allocator);

	configDocument.AddMember(member_name, array_value, *allocator);
}

void Config::GetFloat3(const std::string& name, glm::vec3&returnValue, const glm::vec3&optValue) const
{
	if (!configDocument.HasMember(name.c_str()))
	{
		returnValue = optValue;
	}
	else
	{
		const rapidjson::Value& current_value = configDocument[name.c_str()];
		returnValue = glm::vec3(
			current_value[0].GetFloat(),
			current_value[1].GetFloat(),
			current_value[2].GetFloat()
		);
	}
}

void Config::AddFloat2(const glm::vec2& valueToAdd, const std::string& name)
{
	rapidjson::Value member_name(name.c_str(), *allocator);
	rapidjson::Value array_value(rapidjson::kArrayType);
	array_value.PushBack(valueToAdd.x, *allocator);
	array_value.PushBack(valueToAdd.y, *allocator);

	configDocument.AddMember(member_name, array_value, *allocator);
}

void Config::GetFloat2(const std::string& name, glm::vec2&returnValue, const glm::vec2&optValue) const
{
	if (!configDocument.HasMember(name.c_str()))
	{
		returnValue = optValue;
	}
	else
	{
		const rapidjson::Value& current_value = configDocument[name.c_str()];
		returnValue = glm::vec2(
			current_value[0].GetFloat(),
			current_value[1].GetFloat()
		);
	}
}

void Config::AddQuat(const glm::quat& valueToAdd, const std::string& name)
{
	rapidjson::Value member_name(name.c_str(), *allocator);
	rapidjson::Value quat_value(rapidjson::kArrayType);
	quat_value.PushBack(valueToAdd.x, *allocator);
	quat_value.PushBack(valueToAdd.y, *allocator);
	quat_value.PushBack(valueToAdd.z, *allocator);
	quat_value.PushBack(valueToAdd.w, *allocator);

	configDocument.AddMember(member_name, quat_value, *allocator);
}

void Config::GetQuat(const std::string& name, glm::quat& returnValue, const glm::quat& optValue) const
{
	if (!configDocument.HasMember(name.c_str()))
	{
		returnValue = optValue;
	}
	else
	{
		const rapidjson::Value& current_value = configDocument[name.c_str()];
		returnValue = glm::quat(
			current_value[0].GetFloat(),
			current_value[1].GetFloat(),
			current_value[2].GetFloat(),
			current_value[3].GetFloat()
		);
	}
}

void Config::AddColor(const glm::vec4& valueToAdd, const std::string& name)
{
	rapidjson::Value member_name(name.c_str(), *allocator);
	rapidjson::Value color_value(rapidjson::kArrayType);
	color_value.PushBack(valueToAdd.x, *allocator);
	color_value.PushBack(valueToAdd.y, *allocator);
	color_value.PushBack(valueToAdd.z, *allocator);
	color_value.PushBack(valueToAdd.w, *allocator);

	configDocument.AddMember(member_name, color_value, *allocator);
}

void Config::GetColor(const std::string& name, glm::vec4& returnValue, const glm::vec4& optValue) const
{
	if (!configDocument.HasMember(name.c_str()))
	{
		returnValue = optValue;
	}
	else
	{
		const rapidjson::Value& current_value = configDocument[name.c_str()];
		returnValue = glm::vec4(
			current_value[0].GetFloat(),
			current_value[1].GetFloat(),
			current_value[2].GetFloat(),
			current_value[3].GetFloat()
		);
	}
}

void Config::AddChildConfig(Config& valueToAdd, const std::string& name)
{
	rapidjson::Value member_name(name.c_str(), *allocator);
	rapidjson::Value tmp_value(rapidjson::kObjectType);
	tmp_value.CopyFrom(valueToAdd.configDocument, *allocator);
	configDocument.AddMember(member_name, tmp_value, *allocator);
}

void Config::GetChildConfig(const std::string& name, Config& valueToAdd) const
{
	assert(configDocument.HasMember(name.c_str()));

	const rapidjson::Value& tmp_value = configDocument[name.c_str()];
	valueToAdd = Config(tmp_value);
}

void Config::AddChildrenConfig(std::vector<Config> &valueToAdd, const std::string& name)
{
	rapidjson::Value member_name(name.c_str(), *allocator);
	rapidjson::Value children_configs_value(rapidjson::kArrayType);
	for (unsigned int i = 0; i < valueToAdd.size(); ++i)
	{
		rapidjson::Value tmp_value(rapidjson::kObjectType);
		tmp_value.CopyFrom(valueToAdd[i].configDocument.Move(), *allocator);
		children_configs_value.PushBack(tmp_value.Move(), *allocator);
	}
	configDocument.AddMember(member_name, children_configs_value, *allocator);
}

void Config::GetChildrenConfig(const std::string& name, std::vector<Config>& returnValue) const
{
	if (!configDocument.HasMember(name.c_str()))
	{
		return;
	}

	const rapidjson::Value& children_configs_value = configDocument[name.c_str()];
	returnValue = std::vector<Config>();
	for (unsigned int i = 0; i < children_configs_value.Size(); ++i)
	{
		const rapidjson::Value& tmp_value = children_configs_value[i];
		Config tmp_config(tmp_value);
		returnValue.push_back(tmp_config);
	}
}

void Config::GetSerializedString(std::string& return_string)
{
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

	configDocument.Accept(writer);
	return_string = buffer.GetString();
}
