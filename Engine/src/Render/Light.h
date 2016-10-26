#ifndef SAG_LIGHT_H
#define SAG_LIGHT_H

#include "./Scene/MoveableObject.h"

#include <glm/vec4.hpp>
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

	glm::vec4 getPosition()
	{
		auto test = this->modelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return test;
	}

	LightType getType() { return type; }

private:
	LightType type;
};

} // namespace sag


#endif // SAG_LIGHT_H
