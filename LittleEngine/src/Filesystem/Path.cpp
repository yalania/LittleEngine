#include "Path.h"
#include <Filesystem/File.h>

Path::Path(const std::string& fullPath)
: mFullPath (fullPath)
{
}

std::unique_ptr<File> Path::GetFile() const
{
	return std::make_unique<File>(mFullPath, GetExtension());
}

std::string Path::GetExtension() const
{
	std::size_t found = mFullPath.find_last_of(".");
	if (found == std::string::npos || found == 0) {
		return {};
	}
	std::string file_extension = mFullPath.substr(found + 1, mFullPath.length());

	return file_extension;
}

std::string Path::GetFullPath() const
{
	return mFullPath;
}

std::string Path::GetFilename() const
{
	return mFullPath.substr(mFullPath.find_last_of('/') + 1, -1);
}

std::string Path::GetFilenameWithoutExtension() const
{
	std::string fileName = GetFilename();
	return fileName.substr(0, fileName.find_last_of("."));
}
std::string Path::GetFullPathWithoutExtension() const
{
	return mFullPath.substr(0, mFullPath.find_last_of("."));
}
Path* Path::GetParent() const
{
	return mParent;
}