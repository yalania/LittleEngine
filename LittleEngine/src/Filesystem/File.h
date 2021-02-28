#pragma once
#include <vector>
#include <string>

enum class FileType
{
	ANIMATION,
	ARCHIVE,
	FONT,
	MATERIAL,
	MESH,
	META,
	MODEL,
	PREFAB,
	SCENE,
	SKELETON,
	SKYBOX,
	STATE_MACHINE,
	TEXTURE,
	SOUND,
	UNKNOWN,
	VIDEO
};
enum PHYSFS_FileType;
class File {

public:
	File(const std::string& fullPath, const std::string& extension);
	~File() = default;

	std::vector<char> Open();
	bool Save(const std::vector<char>& data, bool append);
private:

	FileType CalculateFileType(const PHYSFS_FileType& fileType, const std::string& extension) const;
private:
	std::string mFilePath;
	std::vector<char> mLoadedData;
	FileType mFileType;
	bool mIsDirectory = false;
};