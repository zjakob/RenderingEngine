#ifndef SAGAME_LIGHT_MATERIAL_H
#define SAGAME_LIGHT_MATERIAL_H

#include <Render/Material/Material.h>


namespace sagame
{

class LightMaterial : public sag::Material
{
public:
	LightMaterial();
	
	virtual void apply(const glm::mat4& model, const glm::mat4& view, const glm::mat4& modelViewProjection, const std::list<sag::Light*>& lights) override;

private:

};

} // namespace sagame


#endif // SAGAME_LIGHT_MATERIAL_H
