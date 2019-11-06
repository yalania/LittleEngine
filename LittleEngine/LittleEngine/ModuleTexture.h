#ifndef _MODULE_TEXTURE_
#define _MODULE_TEXTURE_
#include "Module.h"

class ModuleTexture : public Module {
public:
	update_status Update() override;
	void LoadTexture(const char * texturePath);
private:
	unsigned int texture;
};

#endif // !_MODULE_TEXTURE_

