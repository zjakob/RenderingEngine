#ifndef SAGAME_CUBE_MATERIAL_H
#define SAGAME_CUBE_MATERIAL_H

#include <Render/Material/Material.h>


namespace sagame
{

class CubeMaterial : public sag::Material
{
public:
	CubeMaterial();
	
	virtual void apply(const glm::mat4& model, const glm::mat4& view, const glm::mat4& modelViewProjection);

private:

};

} // namespace sagame


#endif // SAGAME_CUBE_MATERIAL_H
