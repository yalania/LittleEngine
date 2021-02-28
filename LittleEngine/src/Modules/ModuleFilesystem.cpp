#include "ModuleFilesystem.h"

#include <physfs/physfs.h>

namespace
{
	const char* const LIBRARY_PATH = "Library";
	const char* const ASSETS_PATH = "Assets";
}
ModuleFilesystem::~ModuleFilesystem()
{
	CleanUp();
}

bool ModuleFilesystem::Exists(const std::string& path)
{
	return PHYSFS_exists(path.c_str());
}

bool ModuleFilesystem::MakeDirectory(const std::string& directory)
{
	if (Exists(directory))
	{
		return true;
	}
	if (PHYSFS_mkdir(directory.c_str()) == 0)
	{
		LOG("Error creating directory %s : %s", directory.c_str(), PHYSFS_getLastError());
		return false;
	}
	return true;
}

// Called before render is available
bool ModuleFilesystem::Init()
{
	LOG("************ Module File System Init ************");
	if (PHYSFS_init(nullptr) == 0)
	{
		return false;
	}
	if (PHYSFS_mount(".", "", 0) == 0)
	{
		LOG("Error mounting directory: %s", PHYSFS_getLastError());
		return false;
	}

	if (PHYSFS_setWriteDir(".") == 0)
	{
		LOG("Error creating writing directory: %s", PHYSFS_getLastError());
		return false;
	}

	if (!Exists(LIBRARY_PATH))
	{
		MakeDirectory(LIBRARY_PATH);
	}
	if (!Exists(ASSETS_PATH))
	{
		MakeDirectory(ASSETS_PATH);
	}

	return true;
}

// Called before quitting
bool ModuleFilesystem::CleanUp()
{
	return PHYSFS_deinit();
}