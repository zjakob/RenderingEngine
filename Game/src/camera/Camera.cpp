#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position) :
	fovy(glm::radians(50.0f)),
	aspectRatio((float)800 / (float)800),
	near(0.1f),
	far(1000.f)
{
	projection = glm::perspective(fovy, aspectRatio, near, far);
	view = glm::translate(glm::mat4(1.0f), -position);
}

glm::mat4 Camera::getMvMatrix()
{
	return projection * view;
}

void Camera::move(float x, float y, float z)
{
	view = glm::translate(view, -glm::vec3(x, y, z));
}

void Camera::handleKeyDownEvent(KeyDownEvent& e)
{
	switch (e.getKey())
	{
	case keyboardHelper::KeyboardKey::a:
		move(-0.1f, 0.0f, 0.0f);
		break;
	case keyboardHelper::KeyboardKey::d:
		move(0.1f, 0.0f, 0.0f);
		break;
	case keyboardHelper::KeyboardKey::w:
		move(0.0f, 0.0f, -0.1f);
		break;
	case keyboardHelper::KeyboardKey::s:
		move(0.0f, 0.0f, 0.1f);
		break;
	default:
		break;
	}
}