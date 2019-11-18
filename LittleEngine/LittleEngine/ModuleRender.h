#ifndef _MODULE_RENDER_
#define _MODULE_RENDER_
#include "Module.h"
#include "Components/Mesh.h"

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Entity.h"

class ModuleRender : public Module {
public:
	ModuleRender() = default;
	~ModuleRender();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;
	const Entity& GetEntity() const;

	void AddEntity(const char * model);

	void EnableFaceCulling(bool faceCullingEnabled);
	void EnableClockwiseFaceCulling(bool clockwiseFaceCullingEnabled);
	void SelectFillingMode(int mode);
private:
	void InitOpenGlOptions() const;
	std::unique_ptr<Entity> missingEntity = std::make_unique<Entity>();
	std::vector<std::unique_ptr<Entity>> entities;
};

#endif // !_MODULE_RENDER_

