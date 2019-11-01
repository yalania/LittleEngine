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
	void Translate(const glm::vec4 & direction);
	void Zoom(bool zoomIn);
	void ChangeProjection();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
private:
	glm::mat4 view;
	glm::mat4 projection;

	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // Z position
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //Up position
	glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraFront)); //Right camera vector
	

	float yaw = -90.0f;
	float pitch = 0;

	const float cameraSpeed = 0.05f;
	bool perspectiveEnable = true;
};
#endif // !_MODULE_CAMERA_

