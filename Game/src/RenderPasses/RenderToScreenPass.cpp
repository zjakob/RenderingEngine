
#include "RenderToScreenPass.h"

#include <GL/glew.h>

using namespace sagame;


RenderToScreenPass::RenderToScreenPass(unsigned int renderWindowWidth, unsigned int renderWindowHeight) :
	renderWindowWidth(renderWindowWidth), renderWindowHeight(renderWindowHeight)
{ }

void RenderToScreenPass::render(const sag::SceneManager& scene, sag::RenderPassData* renderPassDataExchange) const
{
	glEnable(GL_CULL_FACE);
	// glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glViewport(0, 0, this->renderWindowWidth, this->renderWindowHeight);

	// clear
	static const GLfloat clearColor[] = { 0.7f, 0.7f, 0.8f, 1.0f };
	static const GLfloat one = 1.0f;

	glClearBufferfv(GL_COLOR, 0, clearColor);
	glClearBufferfv(GL_DEPTH, 0, &one);
	glCullFace(GL_BACK);


	auto camera = scene.getMainCamera();
	const glm::mat4& projection = camera.getProjectionMatrix();
	const glm::mat4& view = camera.getTransformation();
	const glm::mat4 viewProjection = projection * view;

	// draw scene
	auto lights = scene.getLights();
	auto renderableObjects = scene.getRenderableObjects();
	for (auto& renderableObj : renderableObjects)
	{
		renderableObj->render(view, viewProjection, lights, renderPassDataExchange);
	}

	glFlush();
	glFinish();
}
