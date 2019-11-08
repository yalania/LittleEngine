#ifndef _MODULE_MODEL_LOADER_
#define _MODULE_MODEL_LOADER_
#include "Module.h"
#include <string>
#include <assimp/scene.h>

class ModuleModelLoader : public Module {
	void LoadModel(std::string const &pathToModel, std::string const &pathToTexture = "");
	void processNode(aiNode *node, const aiScene *scene);
};
#endif // !_MODULE_MODEL_LOADER_

