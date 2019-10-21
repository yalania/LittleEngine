#ifndef _MODULE_RENDER_
#define _MODULE_RENDER_
#include "Module.h"
class ModuleRender : public Module {
public:
	ModuleRender();
	~ModuleRender() = default;

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	void addVertexBufferObject();
	void loadShaders();


	unsigned int VBO = 0;

};

#endif // !_MODULE_RENDER_

