#include "Importer.h"

#include <ResourceManagement/Metafile/MetafileManager.h>
#include <ResourceManagement/Metafile/Metafile.h>
#include <cassert>

#include <LittleEngine.h>
#include <Modules/ModuleFilesystem.h>
Metafile* Importer::Import(Path& assetsFile)
{
	if (!ImportRequired(assetsFile))
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

	std::string metafileExportedFile = MetafileManager::GetMetafileExportedFolder(*metafile) + std::to_string(metafile->uuid).c_str();
	const auto& metafileExportedPath = Engine->moduleFilesystem->FindOrCreatePath(metafileExportedFile);

	std::vector<char> importedData = ExtractData(assetsFile, *metafile);
	metafileExportedPath->GetFile()->Save(importedData);

	return metafile;
}

bool Importer::ImportRequired(const Path& path)
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
			std::unique_ptr<File> metaFile = path.GetFile();
			return  libraryFile && metaFile  && metaFile->GetModificationTimestamp() > libraryFile->GetModificationTimestamp();
		}
		else
		{
			return false;
		}
	}

	return true;
}

std::vector<char> Importer::ExtractData(Path& assetsFilePath, const Metafile& metafile) const {
	return assetsFilePath.GetFile()->Open();
}
