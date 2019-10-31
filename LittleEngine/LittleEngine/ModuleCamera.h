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
	void Rotate(const glm::vec2 & mouseOffset);
	void Translate(glm::vec4 direction);
	void Zoom(bool zoomIn);

private:
	const float cameraSpeed = 0.01f;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw = -90.0f;
	float pitch = 0;

	glm::mat4 view;
};
#endif // !_MODULE_CAMERA_

