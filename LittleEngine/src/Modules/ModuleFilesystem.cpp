#include "ModuleFilesystem.h"

#include <physfs/physfs.h>

#include <stack>

ModuleFilesystem::~ModuleFilesystem()
{
	CleanUp();
}

bool ModuleFilesystem::Exists(const std::string& path) const
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

	if (!Exists(FilePaths::LIBRARY_PATH))
	{
		MakeDirectory(FilePaths::LIBRARY_PATH);
	}
	if (!Exists(FilePaths::ASSETS_PATH))
	{
		MakeDirectory(FilePaths::ASSETS_PATH);
	}
	mAssets = GetPaths(FilePaths::ASSETS_PATH);

	return true;
}

// Called before quitting
bool ModuleFilesystem::CleanUp()
{
	return PHYSFS_deinit();
}
const std::unique_ptr<Path>& ModuleFilesystem::FindOrCreatePath(const std::string& path)
{
	return std::make_unique<Path>("");
}
Path* ModuleFilesystem::GetPath(const std::string& path)
{
	return nullptr;
}
std::vector<std::unique_ptr<Path>> ModuleFilesystem::GetPaths(const std::string& rootPath) const
{
	std::vector<std::unique_ptr<Path>> paths;

	paths.emplace_back(std::make_unique<Path>(rootPath));

	Path* currentPath = nullptr;
	std::stack<Path*> pathsToAdd;
	pathsToAdd.push(paths.back().get());

	while (!pathsToAdd.empty())
	{
		currentPath = pathsToAdd.top();
		pathsToAdd.pop();

		std::string currentFullPath = currentPath->mFullPath;
		char** files_array = PHYSFS_enumerateFiles(currentFullPath.c_str());
		if (*files_array == NULL)
		{
			LOG("Error reading directory %s: %s", currentFullPath.c_str(), PHYSFS_getLastError());
			return paths;
		}

		char** filename;
		for (filename = files_array; *filename != NULL; filename++)
		{
			if (*filename[0] != '.')
			{
				paths.emplace_back(std::make_unique<Path>(currentFullPath + '/' + *filename));
				currentPath->mChildren.push_back(paths.back().get());
				pathsToAdd.push(currentPath->mChildren.back());
			}
		}
		PHYSFS_freeList(files_array);
	}
	return paths;
}