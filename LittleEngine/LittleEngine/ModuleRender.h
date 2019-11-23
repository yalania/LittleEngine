#ifndef _MODULE_RENDER_
#define _MODULE_RENDER_
#include "Module.h"
#include "Components/Mesh.h"

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "GameObject.h"

class ModuleRender : public Module {
public:
	ModuleRender() = default;
	~ModuleRender();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	void EnableFaceCulling(bool faceCullingEnabled);
	void EnableClockwiseFaceCulling(bool clockwiseFaceCullingEnabled);
	void SelectFillingMode(int mode);
private:
	void InitOpenGlOptions() const;
};

#endif // !_MODULE_RENDER_

