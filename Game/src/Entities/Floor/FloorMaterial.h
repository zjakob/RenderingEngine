#ifndef SAGAME_FLOOR_MATERIAL_H
#define SAGAME_FLOOR_MATERIAL_H

#include <Render/Material/Material.h>


namespace sagame
{

class FloorMaterial : public sag::Material
{
public:
	FloorMaterial();
	
	virtual void apply(const glm::mat4& model, const glm::mat4& view, const glm::mat4& modelViewProjection, const std::list<sag::Light*>& lights, sag::RenderPassData* renderPassDataExchange) override;

private:

};

} // namespace sagame


#endif // SAGAME_FLOOR_MATERIAL_H
