#include "Importer.h"

#include <LittleEngine.h>
#include <Filesystem/Path.h>
#include <Filesystem/File.h>
#include <Modules/ModuleFilesystem.h>
#include <ResourceManagement/Metafile/MetafileManager.h>
#include <ResourceManagement/Metafile/Metafile.h>
#include <cassert>

Importer::Importer(ResourceType resourceType) : mResourceType(resourceType) { mMetafileManager = std::make_unique<MetafileManager>(); };
Importer::~Importer()
{
}

Metafile* Importer::Import(const std::unique_ptr<Path>& assetsFile)
{
	if (!ImportRequired(assetsFile) || assetsFile->GetExtension() == "meta")
	{
		return nullptr;
	}
	Metafile* metafile = mMetafileManager->GetMetafile(assetsFile);

	if (metafile)
	{
		if (metafile->version < Importer::IMPORTER_VERSION)
		{
			MetafileManager::UpdateMetafile(*metafile);
		}
	}
	else
	{
		metafile = mMetafileManager->CreateMetafile(assetsFile, mResourceType);
	}

	const auto& metafileExportedPath = Engine->moduleFilesystem->FindOrCreatePath(metafile->mExportedFilePath);

	std::vector<char> importedData = ExtractData(assetsFile, *metafile);
	metafileExportedPath->GetFile()->Save(importedData);

	return metafile;
}

bool Importer::ImportRequired(const std::unique_ptr<Path>& path)
{
	Metafile* metafile = mMetafileManager->GetMetafile(path);
	if (metafile)
	{
		assert(mMetafileManager->IsMetafileConsistent(*metafile));

		const auto& libraryPath = Engine->moduleFilesystem->FindOrCreatePath(metafile->mExportedFilePath);
		if (metafile->version < Importer::IMPORTER_VERSION || !libraryPath)
		{
			return true;
		}
		else if (libraryPath)
		{
			std::unique_ptr<File> libraryFile = libraryPath->GetFile();
			std::unique_ptr<File> metaFile = path->GetFile();
			return  libraryFile && metaFile  && metaFile->GetModificationTimestamp() > libraryFile->GetModificationTimestamp();
		}
		else
		{
			return false;
		}
	}

	return true;
}

std::vector<char> Importer::ExtractData(const std::unique_ptr<Path>& assetsFilePath, const Metafile& metafile) const {
	return assetsFilePath->GetFile()->Open();
}
