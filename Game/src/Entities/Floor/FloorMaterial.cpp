#include "FloorMaterial.h"

#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Render/Light/DirectionalLight.h>

using namespace sag;
using namespace sagame;


FloorMaterial::FloorMaterial()
{
	shader.attachShader("ShaderSource/shadowmapsecondpass.vs", sag::VERTEX);
	shader.attachShader("ShaderSource/shadowmapsecondpass.fs", sag::FRAGMENT);
	//shader.bindAttribLocation(0, "VertexPosition");
	//shader.bindAttribLocation(1, "VertexNormal");
	shader.link();
}

void FloorMaterial::apply(const glm::mat4& model, const glm::mat4& view, const glm::mat4& modelViewProjection, const std::list<sag::Light*>& lights, sag::RenderPassData* renderPassDataExchange)
{
	if (lights.size() == 0)
		return;
	auto light = lights.back();
	if (auto directionalLight = dynamic_cast<DirectionalLight*>(light))
	{
		GLuint depthTex = renderPassDataExchange->getTexture("depthTex");

		shader.use();

		glm::vec3 color = glm::vec3(0.2f, 0.4f, 0.2f);
		shader.setUniform("Material.Ka", color * 0.05f);
		shader.setUniform("Material.Kd", color);
		shader.setUniform("Material.Ks", glm::vec3(0.2f, 0.7f, 0.2f));
		shader.setUniform("Material.Shininess", 25.0f);


		glm::vec3 lightPos;
		if (lights.size() > 0)
		{
			auto lightPos4 = lights.back()->getPosition();
			lightPos.x = lightPos4.x;
			lightPos.y = lightPos4.y;
			lightPos.z = lightPos4.z;
		}


		shader.setUniform("Light.Intensity", glm::vec3(0.55f));
		shader.setUniform("Light.Position", view * glm::vec4(lightPos, 1.0f));


		auto lightViewMatrix = directionalLight->getView();
		auto lightProjectionMatrix = directionalLight->getPerspective();
		auto shadowBias = glm::mat4(
			glm::vec4(0.5f, 0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.5f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 0.5f, 0.0f),
			glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
			);
		auto lightPV = shadowBias * lightProjectionMatrix * lightViewMatrix;
		shader.setUniform("ShadowMatrix", lightPV * model);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthTex);
		shader.setUniform("ShadowMap", 0);

		shader.setUniform("MVP", modelViewProjection);
		glm::mat4 mv = view * model;
		shader.setUniform("ModelViewMatrix", mv);
		shader.setUniform("NormalMatrix", glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
	}
}
