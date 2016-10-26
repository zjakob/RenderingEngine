#include "CubeMaterial.h"

#include <Render\Light.h>

#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>

using namespace sag;
using namespace sagame;


CubeMaterial::CubeMaterial()
{
	shader.attachShader(".\\src\\ShaderSource\\diffuse.vs", sag::VERTEX);
	shader.attachShader(".\\src\\ShaderSource\\diffuse.fs", sag::FRAGMENT);

	shader.bindAttribLocation(0, "VertexPosition");
	shader.bindAttribLocation(1, "VertexNormal");

	shader.link();
}

void CubeMaterial::apply(const glm::mat4& model, const glm::mat4& view, const glm::mat4& modelViewProjection, const std::list<sag::Light*>& lights)
{
	shader.use();
	// Kd: diffuse reflectivity - fraction of incoming light being scattered
	shader.setUniform("Kd", 0.9f, 0.5f, 0.3f);
	// Ld: light source intensity
	shader.setUniform("Ld", 1.0f, 1.0f, 1.0f);
	glm::vec4 lightPos;
	if (lights.size() > 0)
		lightPos = lights.back()->getPosition();
	shader.setUniform("LightPosition", view * lightPos);

	glm::mat4 mv = view * model;
	shader.setUniform("ModelViewMatrix", mv);
	shader.setUniform("NormalMatrix", glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
	shader.setUniform("MVP", modelViewProjection);
}
