#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include "MoveableObject.h"
#include "../Geometry/Geometry.h"
#include "../Material/Material.h"

#include <utility>

class RenderableObject : public MoveableObject
{
public:
	RenderableObject(Material&& material) :
		material(std::move(material))
	{}

	RenderableObject(Material&& material, Geometry&& geometry) :
		material(std::move(material)), geometry(std::move(geometry))
	{}

	virtual void setGeometry(Geometry&& geometry) { this->geometry = geometry; };

	virtual void render(const glm::mat4& projection) = 0;

protected:

	Material material;
	Geometry geometry;

};

#endif // RENDERABLE_OBJECT_H
