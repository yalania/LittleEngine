#pragma once
#include <Filesystem/File.h>

#include <memory>
#include <string>
#include <assert.h>
class Path;
class Metafile;

enum class ResourceType
{
	ANIMATION = 0,
	SOUND = 1,
	MATERIAL = 2,
	MODEL = 3,
	MESH = 4,
	NAVMESH = 5,
	PREFAB = 6,
	SCENE = 7,
	SKELETON = 8,
	SKYBOX = 9,
	TEXTURE = 10,
	STATE_MACHINE = 11,
	FONT = 12,
	VIDEO = 13,
	UNKNOWN = 14
};

class Resource
{
public:
	Resource() = default;
	Resource(uint32_t uuid);
	Resource& operator=(const Resource& resourceToCopy) = default;

	virtual ~Resource() = default;

	uint32_t GetUUID() const;

	static std::string GetResourceTypeName(ResourceType resource_type);

public:
	bool initialized = false;

protected:
	uint32_t uuid = 0;

};

namespace ResourceManagement
{
	template<typename T>
	static std::vector<char> Binarize(Resource* resource)
	{
		assert(1 != 0); // If you are here, implement your Binarize function on the corresponding resource class.
		return NULL;
	};

	template<typename T>
	static std::shared_ptr<T> Load(uint32_t uuid, const std::vector<char>& resource_data, bool async = false)
	{
		return nullptr;
	};

	template<typename T>
	static std::vector<char> Create()
	{
		assert(1 != 0); // If you are here, implement your Create function on the corresponding resource class.
		return NULL;
	};
}
