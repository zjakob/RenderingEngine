#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>


using namespace sag;

constexpr float defaultNear = 0.1f;
constexpr float defaultFar = 100.0f;

Camera::Camera(float aspectRatio, float fovyDeg) :
	fovy(glm::radians(fovyDeg)),
	aspectRatio(aspectRatio),
	near(defaultNear),
	far(defaultFar)
{
	projection = glm::perspective(fovy, aspectRatio, near, far);
}

const glm::mat4& Camera::getProjectionMatrix() const
{
	return projection;
}
