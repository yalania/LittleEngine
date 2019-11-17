#ifndef _MODULE_TEXTURE_
#define _MODULE_TEXTURE_
#include "Module.h"
#include "Components/Mesh.h"

#include <vector>
#include <string>
#include <assimp/scene.h>
class ModuleTexture : public Module {
public:
	bool Init() override;
	unsigned int LoadTexture(const char *texturePath, const std::string &directory = "");
	std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, std::string directory);
private:
	void GetCheckerboardTexture();
	std::vector<Texture> texturesLoaded;
public:
	unsigned int checkerboardTextureId;
};

#endif // !_MODULE_TEXTURE_

