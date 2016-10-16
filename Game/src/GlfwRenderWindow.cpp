
#include "GlfwRenderWindow.h"

#include <Exception/OpenGLException.h>


using namespace sag;
using namespace sagame;

GlfwRenderWindow::GlfwRenderWindow(unsigned int windowWidth, unsigned int windowHeight) :
	windowWidth(windowWidth),
	windowHeight(windowHeight)
{
	if (!glfwInit())
	{
		throw OpenGLException("Failed to initialize Glfw");
	}
	GLenum error = glGetError(); // get GL-error 1282 to clear glGetError

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#if defined(_DEBUG) || defined(NDEBUG)
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(windowWidth, windowHeight, "Render Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw OpenGLException("Failed to create Glfw window and OpenGL render context");
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
}
	 
GlfwRenderWindow::~GlfwRenderWindow()
{
	glfwTerminate();
}

GLFWwindow* GlfwRenderWindow::getWindow()
{
	return window;
}

bool GlfwRenderWindow::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void GlfwRenderWindow::swapBuffer()
{
	glfwSwapBuffers(window);
}
