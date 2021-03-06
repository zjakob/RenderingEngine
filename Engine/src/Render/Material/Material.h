#ifndef SAG_MATERIAL_H
#define SAG_MATERIAL_H

#include <list>

#include <glm/mat4x4.hpp>
#include <GL/glew.h>

#include "Shader/GlslShaderProgram.h"
#include "../Light/Light.h"
#include "../Renderer/RenderPass/RenderPassData.h"

namespace sag
{

class Material
{
public:
	Material();
	Material(GlslShaderProgram&& shader);
	virtual ~Material();
	Material(Material&& other);
	Material& operator=(Material&& other);
	Material(const Material& other) = default;
	Material& operator=(const Material& other) = default;
	
	virtual void apply(const glm::mat4& model, const glm::mat4& view, const glm::mat4& modelViewProjection, const std::list<Light*>& lights, RenderPassData* renderPassDataExchange) = 0;

protected:
	GlslShaderProgram shader;

};

} // namespace sag


#endif // SAG_MATERIAL_H
