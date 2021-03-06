#pragma once
#include "Module.h"
#include <Filesystem/Path.h>
class Importer;
class ModuleResources : public Module
{
public:

	ModuleResources();
	~ModuleResources();

	bool Init() override;
	bool CleanUp() override;
private:
	std::unique_ptr<Importer> mImporter = nullptr;
};

