#ifndef _MODULE_CAMERA_
#define _MODULE_CAMERA_
#include "Module.h"
#include "GameObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>

class ModuleCamera : public Module {

public:
	bool Init() override;
	UpdateStatus PreUpdate() override;
	void MoveCameraWithMousePosition(const glm::vec2 & mouseOffset);
	void Translate(const glm::vec3 & direction);
	void Zoom(bool zoomIn);
	void FocusOnGameObject(const GameObject & gameObject);
	void OrbitAroundGameObject(const GameObject & gameObject, const glm::vec2 & mouseOffset);
	void UpdateProjection();

	void SetAspectRatio(float newAspectRatio);
	void SetFarPlane(float newFarPlane);
	void SetNearPlane(float newNearPlane);
	void SetPerspectiveEnable(bool perspective);
	void SetHorizontalFov(float horizontalFov);

	float GetAspectRatio()const { return aspect;}
	float GetFarPlane() const { return farPlane;}
	float GetNearPlane() const { return nearPlane;}
	bool GetPerspectiveEnable() const { return perspectiveEnable;}
	float GetHorizontalFov() const { return frustumFov;}

private:
	void UpdateMatricesInShaderPograms();
	GameObject * cameraGameObject;
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view;
private:
	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	float frustumFov = 45.0f;
	float orthoUnits = 1.0f;
	float farPlane = 1000.0f;
	float nearPlane = 0.1f;
	bool perspectiveEnable = true;
public:
	float cameraSpeedKeys = CAMERA_SPEED;
	float cameraSpeedMouse = CAMERA_SPEED;
};
#endif // !_MODULE_CAMERA_

