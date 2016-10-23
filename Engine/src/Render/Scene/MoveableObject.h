#ifndef SAG_MOVEABLE_OBJECT_H
#define SAG_MOVEABLE_OBJECT_H

#include <glm/mat4x4.hpp>

#include "../../util/ComparableObject.h"


namespace sag
{

class MoveableObject : public ComparableObject
{
public:
	MoveableObject() :
		modelMatrix(1.0)
	{

	}

	virtual const glm::mat4& getTransformation() const
	{
		return modelMatrix;
	}

	virtual void setTransformation(const glm::mat4& modelMatrix)
	{
		this->modelMatrix = modelMatrix;
	}

protected:
	glm::mat4 modelMatrix;

};

} // namespace sag


#endif // SAG_MOVEABLE_OBJECT_H
