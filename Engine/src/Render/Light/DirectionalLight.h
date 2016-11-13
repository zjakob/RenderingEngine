#ifndef SAG_DIRECTIONAL_LIGHT_H
#define SAG_DIRECTIONAL_LIGHT_H

#include "Light.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

namespace sag
{

class DirectionalLight : public Light
{
public:
	DirectionalLight(glm::vec3 center, float fovyDeg, float aspect) : 
		center(center),
		perspective(glm::perspective(glm::radians(fovyDeg), aspect, 0.1f, 100.0f))
	{

	}
	
	glm::mat4 getView()
	{
		glm::vec3 lightPos;
		auto lightPos4 = this->getPosition();
		lightPos.x = lightPos4.x;
		lightPos.y = lightPos4.y;
		lightPos.z = lightPos4.z;
		return glm::lookAt(lightPos, this->center, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::mat4 getPerspective()
	{
		return perspective;
	}

private:
	glm::vec3 center;
	glm::mat4 perspective;
};

} // namespace sag


#endif // SAG_DIRECTIONAL_LIGHT_H
