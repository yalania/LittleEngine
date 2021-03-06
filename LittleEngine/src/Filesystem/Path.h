#pragma once
#include <memory>
#include <string>
#include <vector>
class File;
class Path {
public:
	Path(const std::string& fullPath);
	~Path() = default;

	bool IsDirectory() const;
	std::unique_ptr<File> GetFile() const;
	std::string GetExtension() const;
	std::string GetFullPath() const;
	std::string GetFilename() const;

	std::string GetFilenameWithoutExtension() const;
	std::string GetFullPathWithoutExtension() const;

	static std::string GetParentPathString(const std::string& path);

	Path* GetParent() const;

	std::vector<Path*> mChildren;
	const size_t mHash;
private:
	std::string mFullPath;
	Path* mParent = nullptr;
	friend class ModuleFilesystem;
};

