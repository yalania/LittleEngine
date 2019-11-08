#ifndef _MODULE_GRID_
#define _MODULE_GRID_
#include "Module.h"
#include <glm/glm.hpp>

class ModuleGrid : public Module {

public:
	bool Init() override;
	update_status Update() override;

private:
	void ShowGrid() const;
	void ShowDirectionArrows() const;
	GLuint gridShaderProgram;
	glm::mat4 model;

};

#endif // !_MODULE_GRID_

