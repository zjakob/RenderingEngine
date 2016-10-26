#ifndef SAG_RENDERABLE_OBJECT_H
#define SAG_RENDERABLE_OBJECT_H

#include "MoveableObject.h"
#include "../Geometry/Geometry.h"
#include "../Material/Material.h"
#include "../Light.h"

#include <utility>
#include <memory>


namespace sag
{

class RenderableObject : public MoveableObject
{
public:
	RenderableObject(std::unique_ptr<Material> material, std::unique_ptr<Geometry> geometry) :
		material(std::move(material)), geometry(std::move(geometry))
	{

	}

	virtual void render(const glm::mat4& view, const glm::mat4& viewProjection, const std::list<Light*>& lights) = 0;

protected:
	std::unique_ptr<Material> material;
	std::unique_ptr<Geometry> geometry;

};

} // namespace sag


#endif // SAG_RENDERABLE_OBJECT_H
