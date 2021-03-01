#pragma once
#include "Module.h"
#include <Filesystem/Path.h>
class ModuleResources : public Module
{
public:

	ModuleResources() = default;
	~ModuleResources();

	bool Init() override;
	bool CleanUp() override;
private:
};

