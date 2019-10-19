#ifndef _MODULE_RENDER_
#define _MODULE_RENDER_
#include "Module.h"

class ModuleRender : public Module {
public:
	ModuleRender();
	~ModuleRender() {};

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

};

#endif // !_MODULE_RENDER_

