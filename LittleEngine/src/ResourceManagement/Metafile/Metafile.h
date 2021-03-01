#ifndef _METAFILE_H_
#define _METAFILE_H_

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
	uint32_t uuid = 0;
	std::string resourceName;

	ResourceType mResourceType = ResourceType::UNKNOWN;

	std::string mMetafilePath = "";
	std::string mImportedFilePath = "";
	std::string mExportedFilePath = "";

	int version = 0;
};


#endif // _METAFILE_H_

