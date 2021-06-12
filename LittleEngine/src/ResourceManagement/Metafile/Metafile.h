#pragma once
#include "ResourceManagement/Resources/Resource.h"
#include <string>

class Config;

class Metafile
{
public:
	Metafile() = default;
	virtual ~Metafile() = default;

	Metafile(const std::string& path) : mMetafilePath(path) {};

	//Copy and move
	Metafile(const Metafile& metafileToCopy) = default;
	Metafile(Metafile&& metafileToMove) = default;

	Metafile& operator=(const Metafile& metafileToCopy) = default;
	Metafile& operator=(Metafile&& metafileToMove) = default;

	virtual void Save(Config& config) const;
	virtual void Load(const Config& config);

public:
	std::string mResourceName;
	std::string mMetafilePath;
	std::string mImportedFilePath;
	std::string mExportedFilePath;
	int version = 0;
	ResourceType mResourceType = ResourceType::UNKNOWN;
	uint32_t uuid = 0;
};


