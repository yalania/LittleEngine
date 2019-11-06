#ifndef _MODULE_RENDER_
#define _MODULE_RENDER_
#include "Module.h"
#include "VertexBufferObject.h"

#include <vector>
#include <memory>
#include <glm/glm.hpp>


class ModuleRender : public Module {
public:
	ModuleRender() = default;
	~ModuleRender() = default;

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;
	void WindowResized(unsigned width, unsigned height);


private:
	void LoadShaders() const;
	void InitOpenGlOptions() const;
	void GenerateMatrices();
	void ShowGrid() const;
	void ShowDirectionArrows() const;

private:
	std::vector<std::unique_ptr<VertexBufferObject>> objects;
	glm::mat4 model;
};

#endif // !_MODULE_RENDER_

