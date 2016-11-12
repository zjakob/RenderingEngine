#ifndef SAG_CAMERA_H
#define SAG_CAMERA_H

#include <glm\mat4x4.hpp>
#include <glm/glm.hpp>

#include "../Scene/MoveableObject.h"


namespace sag
{

class Camera : public MoveableObject
{

public:
	Camera(float aspectRatio, float fovyDeg);

	const glm::mat4& getProjectionMatrix() const;
	float getFovy() { return glm::degrees(fovy); }

private:
	float fovy;
	float aspectRatio;
	float near;
	float far;

	glm::mat4 projection;
};

} // namespace sag

#endif // SAG_CAMERA_H
