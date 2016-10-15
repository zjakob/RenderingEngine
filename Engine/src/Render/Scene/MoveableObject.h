#ifndef MOVEABLE_OBJECT_H
#define MOVEABLE_OBJECT_H

#include <glm/mat4x4.hpp>

#include "../../util/ComparableObject.h"


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

	virtual void setTransformation(glm::mat4& modelMatrix)
	{
		this->modelMatrix = modelMatrix;
	}

protected:
	glm::mat4 modelMatrix;

};


#endif // MOVEABLE_OBJECT_H
