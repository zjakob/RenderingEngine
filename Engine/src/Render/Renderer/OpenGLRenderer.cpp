
#include "OpenGLRenderer.h"

#include "../../Exception/OpenGLException.h"


using namespace sag;

OpenGLRenderer::OpenGLRenderer(RenderWindow& renderWindow) :
	renderWindow(renderWindow)
{
	init();
}

OpenGLRenderer::~OpenGLRenderer()
{
}

void OpenGLRenderer::init()
{
	if (glewInit())
	{
		throw OpenGLException("Failed to initialize glew");
	}
	GLenum error = glGetError(); // get GL-error 1280 to clear glGetError

	glEnable(GL_CULL_FACE);
	// glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glViewport(0, 0, renderWindow.getWidth(), renderWindow.getHeight());
}

void OpenGLRenderer::render(const std::list<RenderableObject*>& renderableSceneNodes, const Camera& camera)
{
	// clear
	static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;

	glClearBufferfv(GL_COLOR, 0, green);
	glClearBufferfv(GL_DEPTH, 0, &one);

	const glm::mat4& projection = camera.getProjectionMatrix();
	const glm::mat4& view = camera.getTransformation();
	const glm::mat4 viewProjection = projection * view;

	// render
	for (auto& renderableObj : renderableSceneNodes)
	{
		renderableObj->render(view, viewProjection);
	}

	// swap buffer
	renderWindow.swapBuffer();
}
