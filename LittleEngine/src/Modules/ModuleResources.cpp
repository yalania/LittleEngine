#include "ModuleResources.h"
#include "LittleEngine.h"
#include <Modules/ModuleFilesystem.h>
#include <ResourceManagement/Importer/Importer.h>
ModuleResources::ModuleResources()
{
}
ModuleResources::~ModuleResources()
{
	CleanUp();
}

// Called before render is available
bool ModuleResources::Init()
{
	mImporter = std::make_unique<Importer>(ResourceType::UNKNOWN);
	LOG("************ Module Resource Management ************");
	for (const auto& path : Engine->moduleFilesystem->mPaths)
	{
		if (!path->GetExtension().empty())
		{
			mImporter->Import(path);
		}
	}
	return true;
}

bool ModuleResources::CleanUp()
{
	return true;
}
