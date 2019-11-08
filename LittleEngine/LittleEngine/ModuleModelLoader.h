#ifndef _MODULE_MODEL_LOADER_
#define _MODULE_MODEL_LOADER_
#include "Module.h"
#include <string>
#include <assimp/scene.h>
#include "Components/Mesh.h"
class ModuleModelLoader : public Module {
public:
	void LoadModel(std::string const &pathToModel, std::string const &pathToTexture = "");
private:
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	//void ProcessMaterial();
};
#endif // !_MODULE_MODEL_LOADER_

