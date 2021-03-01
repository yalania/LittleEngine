#include "ModuleResources.h"
#include "LittleEngine.h"
#include <Modules/ModuleFilesystem.h>
ModuleResources::~ModuleResources()
{
	CleanUp();
}

// Called before render is available
bool ModuleResources::Init()
{
	LOG("************ Module Resource Management ************");
	for (auto& path : Engine->moduleFilesystem->mAssets)
	{
		if (path->mChildren.size() > 0)
		{
		}
	}
	return true;
}

bool ModuleResources::CleanUp()
{
	return true;
}
