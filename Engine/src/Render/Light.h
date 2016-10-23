#ifndef SAG_LIGHT_H
#define SAG_LIGHT_H

#include "./Scene/MoveableObject.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace sag
{

enum class LightType { Point, Directional, Area };

class Light : public MoveableObject
{
public:
	Light(LightType type) :
		type(type)
	{

	}

	glm::vec3 getPosition()
	{
		return glm::vec3(this->modelMatrix[3]); // return position vector of transformation matrix
	}

	LightType getType() { return type; }

private:
	LightType type;
};

} // namespace sag


#endif // SAG_LIGHT_H
