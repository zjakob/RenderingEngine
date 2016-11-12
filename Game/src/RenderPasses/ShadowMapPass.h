#ifndef SAGAME_SHADOWMAP_PASS_H
#define SAGAME_SHADOWMAP_PASS_H

#include <Render\Material\Shader\GlslShaderProgram.h>
#include <Render\Scene\SceneManager.h>
#include <Render\Renderer\RenderPass\RenderPass.h>
#include <Render\Renderer\RenderPass\RenderPassData.h>


namespace sagame
{

class ShadowMapPass : public sag::RenderPass
{
public:
	ShadowMapPass(float shadowMapWidth, float shadowMapHeight);

	void render(const sag::SceneManager& scene, sag::RenderPassData* renderPassDataExchange) const override;

private:
	GLuint shadowFBO;
	GLuint depthTex;
	sag::GlslShaderProgram shadowShader;
	glm::mat4 shadowBias;
	float shadowMapWidth;
	float shadowMapHeight;

	void setupShaders();
	void setupFBO();

	/**
	 * Writes the depth buffer used for shadow mapping and stored in the FBO to file for debugging.
	 */
	//void writeDepthFboToFile() const;

};

} // namespace sag


#endif // SAGAME_SHADOWMAP_PASS_H
