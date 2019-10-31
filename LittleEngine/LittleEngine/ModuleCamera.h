#ifndef _MODULE_CAMERA_
#define _MODULE_CAMERA_
#include "Module.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ModuleCamera : public Module {

public:
	bool Init() override;
	update_status PreUpdate() override;
	void Rotate(float angle, glm::vec3 direction);
	void Translate(glm::vec3 translation);

private:
	glm::mat4 view;
};
#endif // !_MODULE_CAMERA_

