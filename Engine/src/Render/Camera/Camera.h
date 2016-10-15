#ifndef CAMERA_H
#define CAMERA_H

#include <glm\mat4x4.hpp>

#include "../Scene/MoveableObject.h"

class Camera : public MoveableObject
{

public:
	Camera(float aspectRatio, float fovyDeg);

	const glm::mat4& getProjectionMatrix() const;

private:
	float fovy;
	float aspectRatio;
	float near;
	float far;

	glm::mat4 projection;
};

#endif // CAMERA_H