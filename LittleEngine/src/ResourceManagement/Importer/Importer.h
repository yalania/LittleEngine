#pragma once
#include <Filesystem/Path.h>
#include <Filesystem/File.h>
#include "ResourceManagement/Resources/Resource.h"
#include <vector>
class File;
class Metafile;
class MetafileManager;
class Importer 
{
public:
	Importer() = default;
	Importer(ResourceType resourceType) : mResourceType(resourceType) {};
	virtual ~Importer() = default;

	Metafile* Import(Path& assetsFile);
	virtual std::vector<char> ExtractData(Path& assetsFilePath, const Metafile& metafile) const;

	bool ImportRequired(const Path& path);

public:
	ResourceType mResourceType = ResourceType::UNKNOWN;
	static const int IMPORTER_VERSION = 0;
	std::unique_ptr<MetafileManager> mMetafileManager;
};

