#include "Metafile.h"

#include <FileSystem/Config.h>

void Metafile::Save(Config& config) const
{
	config.AddUInt(uuid, "UUID");
	config.AddString(resourceName, "ResourceName");
	config.AddUInt(static_cast<unsigned int>(mResourceType), "ResourceType");

	assert(!mMetafilePath.empty());
	config.AddString(mMetafilePath, "MetafilePath");
	assert(!mImportedFilePath.empty());
	config.AddString(mImportedFilePath, "ImportedFilePath");
	config.AddString(mExportedFilePath, "ExportedFilePath");

	config.AddInt(version, "ImporterVersion");
}

void Metafile::Load(const Config& config)
{
	uuid = config.GetUInt32("UUID", uuid);
	config.GetString("ResourceName", resourceName, "");
	mResourceType = static_cast<ResourceType>(config.GetUInt("ResourceType",  static_cast<unsigned int>(ResourceType::UNKNOWN)));

	config.GetString("MetafilePath", mMetafilePath, "");
	config.GetString("ImportedFilePath", mImportedFilePath, "");
	config.GetString("ExportedFilePath", mExportedFilePath, "");

	version = config.GetInt("ImporterVersion", 0);
}
