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