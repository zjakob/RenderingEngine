#ifndef SAG_LIGHT_H
#define SAG_LIGHT_H

#include "../Scene/MoveableObject.h"

#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace sag
{

class Light : public MoveableObject
{
public:

	glm::vec4 getPosition()
	{
		return this->modelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}


private:
};

} // namespace sag


#endif // SAG_LIGHT_H
