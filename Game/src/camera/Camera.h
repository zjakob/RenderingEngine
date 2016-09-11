#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <EventSystem\Event\KeyDownEvent.h>

class Camera
{

public:
	Camera(glm::vec3 position);

	glm::mat4 getMvMatrix();

	void handleKeyDownEvent(KeyDownEvent& e);

private:
	glm::vec3 position;
	glm::mat4 view;
	glm::mat4 projection;
	float fovy;
	float aspectRatio;
	float near;
	float far;

	void move(float x, float y, float z);
};

#endif // CAMERA_H