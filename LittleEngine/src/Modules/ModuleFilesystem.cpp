#include "ModuleFilesystem.h"

#include <physfs/physfs.h>
#include <algorithm>
#include <stack>
#include <Filesystem/File.h>
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
	GetPaths(FilePaths::ASSETS_PATH, mPaths);

	return true;
}

// Called before quitting
bool ModuleFilesystem::CleanUp()
{
	return PHYSFS_deinit();
}
UpdateStatus ModuleFilesystem::PostUpdate()
{
	if (!mPathsToBeAdded.empty())
	{
		mPaths.insert(mPaths.end(), std::make_move_iterator(mPathsToBeAdded.begin()), std::make_move_iterator(mPathsToBeAdded.end()));
		mPathsToBeAdded.clear();
	}
	return UpdateStatus();
}

const std::unique_ptr<Path>& ModuleFilesystem::FindOrCreatePath(const std::string& path)
{
	size_t hash = std::hash<std::string>{}(path);
	auto foundPath = std::find_if(mPaths.begin(), mPaths.end(), [&](const std::unique_ptr<Path>& pathInVector) {
		return pathInVector->mHash == hash;
	});
	if (foundPath == mPaths.end())
	{
		return CreateNewPath(path);
	}
	return *foundPath;
}
const std::unique_ptr<Path>& ModuleFilesystem::CreateNewPath(const std::string& path)
{
	auto& newPath = GetPaths(path, mPathsToBeAdded);
	if (!newPath->IsDirectory())
	{
		newPath->GetFile()->Save("");
	}

	size_t parentHash = std::hash<std::string>{}(Path::GetParentPathString(path));
	auto foundParent = std::find_if(mPaths.begin(), mPaths.end(), [&](const std::unique_ptr<Path>& pathInVector) {
		return pathInVector->mHash == parentHash;
	});
	if (foundParent != mPaths.end())
	{
		(*foundParent)->mChildren.push_back(newPath.get());
		newPath->mParent = (*foundParent).get();
	}
	return newPath;
}
Path* ModuleFilesystem::GetPath(const std::string& path) const
{
	size_t hash = std::hash<std::string>{}(path);
	auto foundPath = std::find_if(mPaths.begin(), mPaths.end(), [&](const std::unique_ptr<Path>& pathInVector) {
		return pathInVector->mHash == hash;
	});
	if (foundPath == mPaths.end())
	{
		foundPath = std::find_if(mPathsToBeAdded.begin(), mPathsToBeAdded.end(), [&](const std::unique_ptr<Path>& pathInVector) {
			return pathInVector->mHash == hash;
		});
	}
	if (foundPath == mPathsToBeAdded.end())
	{
		return nullptr;
	}
	return (*foundPath).get();
}
const std::unique_ptr<Path>& ModuleFilesystem::GetPaths(const std::string& rootPath, std::vector<std::unique_ptr<Path>>& paths) const
{
	paths.emplace_back(std::make_unique<Path>(rootPath));
	auto& root = paths.back();
	Path* currentPath = nullptr;
	std::stack<Path*> pathsToAdd;
	pathsToAdd.push(root.get());

	while (!pathsToAdd.empty())
	{
		currentPath = pathsToAdd.top();
		pathsToAdd.pop();

		std::string currentFullPath = currentPath->mFullPath;
		char** files_array = PHYSFS_enumerateFiles(currentFullPath.c_str());
		if (*files_array == NULL)
		{
			LOG("Error reading directory %s: %s", currentFullPath.c_str(), PHYSFS_getLastError());
			return root;
		}

		char** filename;
		for (filename = files_array; *filename != NULL; filename++)
		{
			if (*filename[0] != '.')
			{
				paths.emplace_back(std::make_unique<Path>(currentFullPath + '/' + *filename));
				const auto& newPath = paths.back().get();
				currentPath->mChildren.push_back(newPath);
				newPath->mParent = currentPath;
				if (newPath->IsDirectory())
				{
					pathsToAdd.push(newPath);
				}
			}
		}
		PHYSFS_freeList(files_array);
	}
	return root;
}