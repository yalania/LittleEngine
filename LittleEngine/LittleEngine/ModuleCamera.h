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
	void MoveCameraWithMousePosition(const glm::vec2 & mouseOffset);
	void Translate(const glm::vec2 & direction);
	void Zoom(bool zoomIn);
	void EnablePerspective();
	void EnableOrthographic();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	void LoadProjection();
private:
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // Z position
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //Up position
	glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraFront)); //Right camera vector
	

	float yaw = -90.0f;
	float pitch = 0;
	float frustumFov = 45.0f;
	float orthoUnits = 1.0f;

	const float cameraSpeed = 0.05f;

public:
	bool perspectiveEnable = true;
};
#endif // !_MODULE_CAMERA_

