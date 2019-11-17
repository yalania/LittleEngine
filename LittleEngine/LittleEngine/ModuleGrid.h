#ifndef _MODULE_GRID_
#define _MODULE_GRID_
#include "Module.h"
#include <glm/glm.hpp>

class ModuleGrid : public Module {

public:
	~ModuleGrid();
	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	void ShowGrid() const;
	void ShowDirectionArrows() const;
	glm::mat4 model;
	GLuint gridShaderProgram;
};

#endif // !_MODULE_GRID_

