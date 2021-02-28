#pragma once
#include "Module.h"


class ModuleFilesystem : public Module
{
public:

	ModuleFilesystem() = default;
	~ModuleFilesystem();

	bool Exists(const std::string& path);
	bool MakeDirectory(const std::string& directory);
	bool Init() override;
	bool CleanUp() override;
};

