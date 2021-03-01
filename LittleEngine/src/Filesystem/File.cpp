#include "File.h"
#include <Log.h>
#include <physfs/physfs.h>

File::File(const std::string& fullPath, const std::string& extension)
	: mFilePath(fullPath)
{
	PHYSFS_Stat file_info;
	if (PHYSFS_stat(mFilePath.c_str(), &file_info) == 0)
	{
		LOG("Error getting %s file info: %s", mFilePath.c_str(), PHYSFS_getLastError())
	}
	mIsDirectory = (PHYSFS_FileType::PHYSFS_FILETYPE_DIRECTORY == file_info.filetype);
	if (!mIsDirectory)
	{
		mFileType = CalculateFileType(file_info.filetype, extension);
	}
}

std::vector<char> File::Open()
{
	if (mIsDirectory)
	{
		return mLoadedData;
	}
	PHYSFS_File* physfs_file_handle = PHYSFS_openRead(mFilePath.c_str());
	if (physfs_file_handle == NULL)
	{
		LOG("Error loading file %s, %s", mFilePath.c_str(), PHYSFS_getLastError())
		return mLoadedData;

	}

	size_t res_size = static_cast<size_t>(PHYSFS_fileLength(physfs_file_handle));
	mLoadedData.resize(res_size+1);
	int length_read = static_cast<int>(PHYSFS_read(physfs_file_handle, &mLoadedData.front(), 1, res_size));
	PHYSFS_close(physfs_file_handle);

	if (length_read != res_size)
	{
		LOG("Error loading file %s", mFilePath.c_str())
		return mLoadedData;
	}

	return mLoadedData;
}

bool File::Save(const std::vector<char>& data, bool append)
{
	if (data.size() == 0 || mIsDirectory)
	{
		return false;
	}
	PHYSFS_File* file;
	if (append)
	{
		file = PHYSFS_openAppend(mFilePath.c_str());
	}
	else
	{
		file = PHYSFS_openWrite(mFilePath.c_str());
	}

	if (file == NULL)
	{
		LOG("Error: Unable to open file! PhysFS Error: %s\n", PHYSFS_getLastError());
		return false;
	}

	PHYSFS_writeBytes(file, &data.front(), data.size());
	LOG("File %s saved!\n", mFilePath.c_str());
	PHYSFS_close(file);
	return true;
}

bool File::Save(const std::string& serializedData, bool append)
{
	std::vector<char> data(serializedData.begin(), serializedData.end());
	return Save(data,append);
}

std::string File::GetFullPath() const
{
	return mFilePath;
}

FileType File::GetFileType() const
{
	return mFileType;
}

uint32_t File::GetModificationTimestamp() const
{
	PHYSFS_Stat path_info;
	if (PHYSFS_stat(mFilePath.c_str(), &path_info) == 0)
	{
		LOG("Error getting %s path info: %s", mFilePath.c_str(), PHYSFS_getLastError());
	}

	return path_info.modtime;
}


FileType File::CalculateFileType(const PHYSFS_FileType& fileType, const std::string& extension) const
{
	if (
		extension == "png"
		|| extension == "tif"
		|| extension == "dds"
		|| extension == "tga"
		|| extension == "jpg"
		|| extension == "jfif"
		)
	{
		return FileType::TEXTURE;
	}
	if (extension == "fbx")
	{
		return FileType::MODEL;
	}
	if (extension == "prefab")
	{
		return FileType::PREFAB;
	}
	if (extension == "mesh")
	{
		return FileType::MESH;
	}
	if (extension == "mat")
	{
		return FileType::MATERIAL;
	}
	if (extension == "meta")
	{
		return FileType::META;
	}
	if (extension == "scene")
	{
		return FileType::SCENE;
	}
	if (extension == "sk")
	{
		return FileType::SKELETON;
	}
	if (extension == "skybox")
	{
		return FileType::SKYBOX;
	}
	if (extension == "anim")
	{
		return FileType::ANIMATION;
	}
	if (extension == "stm")
	{
		return FileType::STATE_MACHINE;
	}
	if (extension == "ttf")
	{
		return FileType::FONT;
	}
	if (extension == "bnk")
	{
		return FileType::SOUND;
	}
	if (extension == "mp4")
	{
		return FileType::VIDEO;
	}
	if (extension == "" && PHYSFS_FileType::PHYSFS_FILETYPE_OTHER == fileType)
	{
		return FileType::ARCHIVE;
	}
	return FileType::UNKNOWN;
}