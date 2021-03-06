#pragma once
#include "Module.h"
#include <Filesystem/Path.h>
namespace FilePaths
{
	const char* const LIBRARY_PATH = "Library";
	const char* const ASSETS_PATH = "Assets";
}
class ModuleFilesystem : public Module
{
public:

	ModuleFilesystem() = default;
	~ModuleFilesystem();

	bool Exists(const std::string& path) const;
	bool MakeDirectory(const std::string& directory);
	bool Init() override;
	bool CleanUp() override;
	UpdateStatus PostUpdate() override;

	const std::unique_ptr<Path>& FindOrCreatePath(const std::string& path);
	const std::unique_ptr<Path>& CreateNewPath(const std::string& path);
	Path* GetPath(const std::string& path) const;

	std::vector<std::unique_ptr<Path>> mPaths;
private:
	const std::unique_ptr<Path>& GetPaths(const std::string& rootPath, std::vector<std::unique_ptr<Path>>& paths) const;
	std::vector<std::unique_ptr<Path>> mPathsToBeAdded;
};

