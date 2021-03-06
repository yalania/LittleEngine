#pragma once
#include <string>
#include <unordered_map>
#include <memory>
class Metafile;
class Path;
class File;
enum class ResourceType;

class MetafileManager
{
public:
	MetafileManager() = default;
	~MetafileManager();

	Metafile* CreateMetafile(const std::unique_ptr<Path>& assetFilePath, ResourceType resourceType, uint32_t uuid = 0);

	void SaveMetafile(Metafile* created_metafile) const;
	
	Metafile* GetMetafile(const std::unique_ptr<Path>& metafilePath);

	Metafile* GetMetafile(const std::unique_ptr<File>& metafile);

	std::string GetMetafilePath(const std::unique_ptr<Path>& file_path) const;
	std::string GetMetafilePath(const std::string& file_path_string) const;

	static std::string GetMetafileExportedFolder(const Metafile& metafile);
	static std::string GetUUIDExportedFolder(uint32_t uuid);

	static std::string GetMetafileExportedFile(const Metafile& metafile);
	static std::string GetUUIDExportedFile(uint32_t uuid);

	bool IsMetafileConsistent(const Metafile& metafile);

	static void UpdateMetafile(Metafile& metafile);

private:
	std::unordered_map<std::string, Metafile*> metafiles;
	Metafile* CreateSpecializedMetafile(ResourceType resourceType) const;

	uint32_t GenerateUUID() const;
	/*
	A metafile is consistent when both imported path and exported path exist
		*/
	bool IsMetafileConsistent(const std::unique_ptr<Path>& metafilePath);
	bool IsMetafileMoved(const std::unique_ptr<Path>& metafilePath);
	void RefreshMetafile(const std::unique_ptr<Path>& metafilePath);
};