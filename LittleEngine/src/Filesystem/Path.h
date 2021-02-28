#pragma once
#include <memory>
#include <string>
#include <vector>
class File;
class Path {
public:
	Path(const std::string& fullPath);
	~Path() = default;

	std::unique_ptr<File> GetFile() const;
	std::string GetExtension() const;

private:
	std::string mFullPath;
	std::vector<Path*> mChildren;
	friend class ModuleFilesystem;
};

