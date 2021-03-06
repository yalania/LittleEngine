#pragma once
#include <rapidjson/document.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>
#include <string>
class Config
{
public:
	Config();
	Config(const std::vector<char> & data);
	Config(const rapidjson::Value& object_value);
	Config(const std::string& serialized_scene_string);
	~Config() = default;
	
	Config(const Config& other);
	Config& operator=(const Config& other);

	rapidjson::Document::AllocatorType& GetAllocator() const;

	void AddInt(int valueToAdd, const std::string &name);
	int GetInt(const std::string &name, int optValue) const;

	void AddUInt(uint64_t valueToAdd, const std::string& name);
	uint64_t GetUInt(const std::string& name, unsigned int optValue) const;

	void AddUInt32(uint32_t valueToAdd, const std::string& name);
	uint32_t GetUInt32(const std::string& name, unsigned int optValue) const;

	void AddInt64(int64_t valueToAdd, const std::string &name);
	int64_t GetInt64(const std::string& name, int64_t optValue) const;

	void AddFloat(float valueToAdd, const std::string& name);
	float GetFloat(const std::string &name, float optValue) const;

	void AddBool(bool valueToAdd, const std::string& name);
	bool GetBool(const std::string& name, bool optValue) const;

	void AddString(const std::string valueToAdd, const std::string& name);
	void GetString(const std::string& name, std::string& returnValue, const std::string& optValue) const;

	void AddFloat3(const glm::vec3 &valueToAdd, const std::string& name);
	void GetFloat3(const std::string &name, glm::vec3& returnValue, const glm::vec3 &optValue) const;

	void AddFloat2(const glm::vec2 &valueToAdd, const std::string& name);
	void GetFloat2(const std::string &name, glm::vec2 &returnValue, const glm::vec2& optValue) const;

	void AddQuat(const glm::quat& valueToAdd, const std::string& name);
	void GetQuat(const std::string& name, glm::quat& returnValue, const glm::quat& optValue) const;

	void AddColor(const glm::vec4& valueToAdd, const std::string& name);
	void GetColor(const std::string& name, glm::vec4& returnValue, const glm::vec4& optValue) const;

	void AddChildConfig(Config& valueToAdd, const std::string& name);
	void GetChildConfig(const std::string& name, Config& valueToAdd) const;

	void AddChildrenConfig(std::vector<Config>& valueToAdd, const std::string& name);
	void GetChildrenConfig(const std::string& name, std::vector<Config>& returnValue) const;

	template<class T>
	void AddVector(const std::vector<T>& valueToAdd, const std::string& name)
	{
		rapidjson::Value memberName(name.c_str(), *allocator);
		rapidjson::Value vectorValue(rapidjson::kArrayType);
		for (size_t i = 0; i < valueToAdd.size(); ++i)
		{
			vectorValue.PushBack(valueToAdd[i], *allocator);
		}

		configDocument.AddMember(memberName, vectorValue, *allocator);
	};

	template<>
	void AddVector(const std::vector<std::string>& valueToAdd, const std::string& name)
	{
		rapidjson::Value memberName(name.c_str(), *allocator);
		rapidjson::Value vectorValue(rapidjson::kArrayType);
		for (size_t i = 0; i < valueToAdd.size(); ++i)
		{
			rapidjson::Value stringValue(valueToAdd[i].c_str(), static_cast<rapidjson::SizeType>(valueToAdd[i].size()), *allocator);
			vectorValue.PushBack(stringValue, *allocator);
		}

		configDocument.AddMember(memberName, vectorValue, *allocator);
	};

	template<>
	void AddVector(const std::vector<glm::vec3>& valueToAdd, const std::string& name)
	{
		rapidjson::Value memberName(name.c_str(), *allocator);
		rapidjson::Value vectorValue(rapidjson::kArrayType);
		for (size_t i = 0; i < valueToAdd.size(); ++i)
		{
			rapidjson::Value array_value(rapidjson::kArrayType);
			array_value.PushBack(valueToAdd[i].x, *allocator);
			array_value.PushBack(valueToAdd[i].y, *allocator);
			array_value.PushBack(valueToAdd[i].z, *allocator);

			vectorValue.PushBack(array_value, *allocator);
		}

		configDocument.AddMember(memberName, vectorValue, *allocator);
	};

	template<class T> void GetVector(const std::string& name, std::vector<T>& returnValue, const std::vector<T>& optValue) const
	{
		if (!configDocument.HasMember(name.c_str()))
		{
			returnValue = optValue;
		}
		else
		{
			const rapidjson::Value& currentValue = configDocument[name.c_str()];
			returnValue = std::vector<T>();
			for (size_t i = 0; i < currentValue.Capacity(); ++i)
			{
				returnValue.push_back(currentValue[i].Get<T>());
			}
		}
	};

	template<>
	void GetVector(const std::string& name, std::vector<std::string>& returnValue, const std::vector<std::string>& optValue) const
	{
		if (!configDocument.HasMember(name.c_str()))
		{
			returnValue = optValue;
		}
		else
		{
			const rapidjson::Value& currentValue = configDocument[name.c_str()];
			returnValue = std::vector<std::string>();
			for (rapidjson::SizeType i = 0; i < currentValue.Capacity(); ++i)
			{
				returnValue.push_back(currentValue[i].GetString());
			}
		}
	};

	template<>
	void GetVector(const std::string& name, std::vector<glm::vec3>& returnValue, const std::vector<glm::vec3>& optValue) const
	{
		if (!configDocument.HasMember(name.c_str()))
		{
			returnValue = optValue;
		}
		else
		{
			const rapidjson::Value& currentValue = configDocument[name.c_str()];
			returnValue = std::vector<glm::vec3>();

			for (rapidjson::SizeType i = 0; i < currentValue.Capacity(); ++i)
			{
				const rapidjson::Value& currentFloat3Value = currentValue[i];
				returnValue.push_back(
					glm::vec3(
						currentFloat3Value[0].GetFloat(),
						currentFloat3Value[1].GetFloat(),
						currentFloat3Value[2].GetFloat()
					)
				);
			}
		}
	};

	void GetSerializedString(std::string& return_string);

public:
	rapidjson::Document configDocument;
	rapidjson::Document::AllocatorType* allocator;

};
