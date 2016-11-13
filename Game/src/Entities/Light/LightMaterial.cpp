#include "LightMaterial.h"

#include <Render/Light/Light.h>

#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>

using namespace sag;
using namespace sagame;


LightMaterial::LightMaterial()
{
	shader.attachShader("./src/ShaderSource/solidcolor.vs", sag::VERTEX);
	shader.attachShader("./src/ShaderSource/solidcolor.fs", sag::FRAGMENT);

	shader.bindAttribLocation(0, "VertexPosition");

	shader.link();
}

void LightMaterial::apply(const glm::mat4& model, const glm::mat4& view, const glm::mat4& modelViewProjection, const std::list<sag::Light*>& lights, sag::RenderPassData* renderPassDataExchange)
{
	shader.use();
	shader.setUniform("Color", glm::vec4(1.0f, 1.0f, 0.9f, 1.0f));
	shader.setUniform("MVP", modelViewProjection);
}
