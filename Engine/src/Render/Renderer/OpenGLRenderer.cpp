
#include "OpenGLRenderer.h"

#include "../Camera/Camera.h"
#include "../Light/Light.h"
#include "../../Scene/SceneNode.h"
#include "../../util/Exceptions/OpenGLException.h"


using namespace sag;

OpenGLRenderer::OpenGLRenderer(RenderWindow& renderWindow) :
	renderWindow(renderWindow)
{
	if (glewInit())
	{
		throw OpenGLException("Failed to initialize glew");
	}
	GLenum error = glGetError(); // get GL-error 1280 to clear glGetError
}

void OpenGLRenderer::render(SceneManager& scene)
{
	std::unique_ptr<RenderPassData> renderPassDataExchange = std::make_unique<RenderPassData>();
	for (auto& renderPass : renderPasses)
	{
		renderPass->render(scene, renderPassDataExchange.get());
	}

	renderWindow.swapBuffer();
}

void OpenGLRenderer::addRenderPass(RenderPass* pass)
{
	renderPasses.push_back(pass);
}
