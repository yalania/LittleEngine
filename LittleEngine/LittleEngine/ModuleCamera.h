#ifndef _MODULE_CAMERA_
#define _MODULE_CAMERA_
#include "Module.h"
#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Components/Transform.h"

class ModuleCamera : public Module {

public:
	bool Init() override;
	update_status PreUpdate() override;
	void MoveCameraWithMousePosition(const glm::vec2 & mouseOffset);
	void Translate(const glm::vec3 & direction);
	void Zoom(bool zoomIn);
	void FocusOnEntity(const Entity & entity);

	void EnablePerspective();
	void EnableOrthographic();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

	float frustumFov = 45.0f;
	float orthoUnits = 1.0f;
	float cameraSpeed = CAMERA_SPEED;
	float farPlane = 100.0f;
	float nearPlane = 0.1f;
	void LoadProjection();
private:
	void UpdateMatricesInShaderPograms();
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view;
	Transform transform;
	float yaw = -90.0f;
	float pitch = 0;


public:
	bool perspectiveEnable = true;
};
#endif // !_MODULE_CAMERA_

