#include "MetafileManager.h"

#include <LittleEngine.h>
#include <Modules/ModuleFilesystem.h>
#include <Filesystem/Path.h>
#include <Filesystem/Config.h>
#include "Metafile.h"
#include "ResourceManagement/Importer/Importer.h"
#include "ResourceManagement/Resources/Resource.h"

#include <chrono>

MetafileManager::~MetafileManager()
{
	for (auto& metafile : metafiles)
	{
		delete metafile.second;
	}
	metafiles.clear();
}

Metafile* MetafileManager::GetMetafile(const std::unique_ptr<Path>& assetsFilePath)
{
	const auto& metafilePath = Engine->moduleFilesystem->GetPath(GetMetafilePath(assetsFilePath));
	if (!metafilePath)
	{
		return nullptr;
	}
	if ( metafiles.find(metafilePath->GetFullPath()) != metafiles.end())
	{
		return metafiles[metafilePath->GetFullPath()];
	}

	std::unique_ptr<File> metafile = metafilePath->GetFile();
	return GetMetafile(metafile);
}
Metafile* MetafileManager::GetMetafile(const std::unique_ptr<File>& metafile)
{
	std::vector<char> metafileData = metafile->Open();
	Config metaConfig(metafileData);

	Metafile* createdMetafile = CreateSpecializedMetafile(ResourceType::UNKNOWN);
	createdMetafile->Load(metaConfig);
	Metafile* specializedMetafile = CreateSpecializedMetafile(createdMetafile->mResourceType);
	delete createdMetafile;

	specializedMetafile->Load(metaConfig);
	specializedMetafile->mMetafilePath = specializedMetafile->mMetafilePath.empty() ? metafile->GetFullPath() : specializedMetafile->mMetafilePath;
	metafiles[specializedMetafile->mMetafilePath] = specializedMetafile;

	return specializedMetafile;
}

Metafile* MetafileManager::CreateMetafile(const std::unique_ptr<Path>& assetFilePath, ResourceType resource_type, uint32_t uuid)
{

	Metafile* createdMetafile = CreateSpecializedMetafile(resource_type);

	std::string metafilePath_string = GetMetafilePath(assetFilePath);

	createdMetafile->uuid = uuid == 0 ? GenerateUUID() : uuid;
	createdMetafile->resourceName = assetFilePath->GetFilenameWithoutExtension();
	createdMetafile->mResourceType = resource_type;

	createdMetafile->mMetafilePath = metafilePath_string;
	createdMetafile->mImportedFilePath = assetFilePath->GetFullPath();
	createdMetafile->mExportedFilePath = GetMetafileExportedFile(*createdMetafile);

	createdMetafile->version = Importer::IMPORTER_VERSION;

	SaveMetafile(createdMetafile);

	metafiles[createdMetafile->mMetafilePath] = createdMetafile;

	return createdMetafile;
}

void MetafileManager::SaveMetafile(Metafile* created_metafile) const
{
	Config metafileConfig;
	created_metafile->Save(metafileConfig);

	std::string metafileConfigString;
	metafileConfig.GetSerializedString(metafileConfigString);

	const auto& path = Engine->moduleFilesystem->FindOrCreatePath(created_metafile->mMetafilePath);
	path->GetFile()->Save(metafileConfigString);
}

std::string MetafileManager::GetMetafilePath(const std::unique_ptr<Path>& filePath) const
{
	return GetMetafilePath(filePath->GetFullPath());
}

std::string MetafileManager::GetMetafilePath(const std::string& filePathString) const
{
	return filePathString + ".meta";
}

void MetafileManager::UpdateMetafile(Metafile& metafile)
{
	metafile.version = Importer::IMPORTER_VERSION;

	Config metafileConfig;
	metafile.Save(metafileConfig);

	std::string metafileConfigString;
	metafileConfig.GetSerializedString(metafileConfigString);

	const auto& metafilePath = Engine->moduleFilesystem->FindOrCreatePath(metafile.mMetafilePath);
	metafilePath->GetFile()->Save(metafileConfigString);
}

bool MetafileManager::IsMetafileConsistent(const std::unique_ptr<Path>& metafilePath)
{
	Metafile* metafile = GetMetafile(metafilePath);
	if (!metafile)
	{
		return false;
	}
	return IsMetafileConsistent(*metafile);
}

bool MetafileManager::IsMetafileConsistent(const Metafile& metafile)
{
	Path* importedFilePath = Engine->moduleFilesystem->GetPath(metafile.mImportedFilePath);

	std::string metafile_directory = Path::GetParentPathString(metafile.mMetafilePath);
	std::string imported_file_directory = Path::GetParentPathString(metafile.mImportedFilePath);
	if (metafile_directory != imported_file_directory)
	{
		return false;
	}

	return true;
}

bool MetafileManager::IsMetafileMoved(const std::unique_ptr<Path>& metafilePath)
{
	Metafile* metafile = GetMetafile(metafilePath);
	return metafile->mMetafilePath != metafilePath->GetFullPath();
}

void MetafileManager::RefreshMetafile(const std::unique_ptr<Path>& metafilePath)
{
	std::string assets_file = metafilePath->GetFullPathWithoutExtension();
	Path* newImportedFilePath = Engine->moduleFilesystem->GetPath(assets_file);
	if (!newImportedFilePath)
	{
		return;
	}
	Metafile* metafile = GetMetafile(metafilePath);
	metafile->mMetafilePath = metafilePath->GetFullPath();
	metafile->mImportedFilePath = newImportedFilePath->GetFullPath();
	metafile->resourceName = newImportedFilePath->GetFilename();
	SaveMetafile(metafile);
}

std::string MetafileManager::GetMetafileExportedFolder(const Metafile& metafile)
{
	return GetUUIDExportedFolder(metafile.uuid);
}

std::string MetafileManager::GetUUIDExportedFolder(uint32_t uuid)
{
	std::string uuid_string = std::to_string(uuid);
	return std::string(FilePaths::LIBRARY_PATH) + "/" + uuid_string.substr(0, 2);
}

std::string MetafileManager::GetMetafileExportedFile(const Metafile& metafile)
{
	return GetUUIDExportedFile(metafile.uuid);
}

std::string MetafileManager::GetUUIDExportedFile(uint32_t uuid)
{
	std::string uuid_string = std::to_string(uuid);
	return std::string(FilePaths::LIBRARY_PATH) + "/" + uuid_string.substr(0, 2) + "/" + uuid_string;
}

Metafile * MetafileManager::CreateSpecializedMetafile(ResourceType resource_type) const
{
	Metafile* metafile;
	switch (resource_type)
	{
		default:
			metafile = new Metafile();
			break;
	}
	return metafile;
}

uint32_t MetafileManager::GenerateUUID() const
{
	return uint32_t();
}
