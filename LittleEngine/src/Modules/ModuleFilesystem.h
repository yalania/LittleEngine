#pragma once
#include "Module.h"
#include <Filesystem/Path.h>
class ModuleFilesystem : public Module
{
public:

	ModuleFilesystem() = default;
	~ModuleFilesystem();

	bool Exists(const std::string& path) const;
	bool MakeDirectory(const std::string& directory);
	bool Init() override;
	bool CleanUp() override;
private:
	std::vector<std::unique_ptr<Path>> GetPaths(const std::string& rootPath) const;
	std::vector<std::unique_ptr<Path>> mAssets;
};

