#ifndef _MODULE_MODEL_LOADER_
#define _MODULE_MODEL_LOADER_
#include "Module.h"
#include <string>
#include <assimp/scene.h>
#include "Components/Mesh.h"
#include "Components/Model.h"
class ModuleModelLoader : public Module {
public:
	Model LoadModel(std::string const &pathToModel, std::string const &pathToTexture = "");
private:
	void ProcessNode(const aiNode &node, const aiScene &scene, std::vector<Mesh> & meshes) const;
	Mesh ProcessMesh(const aiMesh &mesh, const aiScene &scene) const;
	void ProcessMaterial(std::vector<std::shared_ptr<Texture>> &textures, const aiMesh &mesh, const aiScene &scene) const;

	std::string textureDirectory;
};
#endif // !_MODULE_MODEL_LOADER_

