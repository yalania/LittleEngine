#ifndef _MODULE_RENDER_
#define _MODULE_RENDER_
#include "Module.h"
#include "VertexBufferObject.h"
#include <vector>
#include <memory>

class ModuleRender : public Module {
public:
	ModuleRender() = default;
	~ModuleRender() = default;

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;

private:
	void LoadShaders() const;
	void InitOpenGlOptions() const;

private:
	std::vector<std::unique_ptr<VertexBufferObject>> objects;

};

#endif // !_MODULE_RENDER_

