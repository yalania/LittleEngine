#ifndef _MODULE_RENDER_
#define _MODULE_RENDER_
#include "Module.h"
#include "VertexBufferObject.h"
#include "Components/Mesh.h"

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Entity.h"


class ModuleRender : public Module {
public:
	ModuleRender() = default;
	~ModuleRender() = default;

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	void AddEntity(const char * model);
private:
	void InitOpenGlOptions() const;

private:
	std::vector<std::unique_ptr<VertexBufferObject>> objects;
	std::vector<std::unique_ptr<Entity>> entities;
	glm::mat4 model;
};

#endif // !_MODULE_RENDER_

