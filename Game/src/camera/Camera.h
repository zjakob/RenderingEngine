#ifndef CAMERA_H
#define CAMERA_H

#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

#include <EventSystem\Event\KeyDownEvent.h>
#include <EventSystem\Event\MouseMoveEvent.h>

class Camera
{

public:
	Camera(glm::vec3&& position, float aspectRatio, float fovyDeg);

	glm::mat4 getVpMatrix();

	void handleKeyDownEvent(KeyDownEvent& e);
	void handleMouseMoveEvent(MouseMoveEvent& e);

private:
	float fovy;
	float aspectRatio;
	float near;
	float far;
	const float mouseSensitivity;
	const float keySensitivity;

	glm::mat4 view;
	glm::mat4 projection;

	float totalYaw;
	float totalPitch;

	glm::vec3 actualTargetOffset;
	glm::vec3 position;
	glm::vec3 left;
	glm::vec3 targetOffset;
	glm::vec3 up;

	void updateViewMatrix();
};

#endif // CAMERA_H