#pragma once
#include "ResourceManagement/Resources/Resource.h"
#include <vector>
class Path;
class Metafile;
class MetafileManager;
class Importer 
{
public:
	Importer(ResourceType resourceType);
	virtual ~Importer();

	Metafile* Import(const std::unique_ptr<Path>& assetsFile);
	virtual std::vector<char> ExtractData(const std::unique_ptr<Path>& assetsFilePath, const Metafile& metafile) const;

	bool ImportRequired(const std::unique_ptr<Path>& path);

public:
	ResourceType mResourceType = ResourceType::UNKNOWN;
	static const int IMPORTER_VERSION = 0;
	std::unique_ptr<MetafileManager> mMetafileManager = nullptr;
};

