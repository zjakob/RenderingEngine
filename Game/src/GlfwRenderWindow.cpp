
#include "GlfwRenderWindow.h"

#include <Exception/OpenGLException.h>

#include <EventSystem\MouseEventManager.h>
#include <EventSystem\KeyboardEventManager.h>
#include <util\ioHelper\keyboardHelper.h>


float mousePosX = 0.0f;
float mousePosY = 0.0f;
bool mouseMoved = false;
static void glfwMouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	mousePosX = (float)xpos;
	mousePosY = (float)ypos;
	mouseMoved = true;
}

bool keysDown[1024];
static void glfwKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keysDown[key] = true;
		else if (action == GLFW_RELEASE)
			keysDown[key] = false;
	}
}

using namespace sag;
using namespace sagame;

GlfwRenderWindow::GlfwRenderWindow(unsigned int windowWidth, unsigned int windowHeight) :
	windowWidth(windowWidth),
	windowHeight(windowHeight),
	screenCenterX(windowWidth / 2.0f),
	screenCenterY(windowHeight / 2.0f)
{
	if (!glfwInit())
	{
		throw OpenGLException("Failed to initialize Glfw");
	}


	/*** init OpenGL ***/
	GLenum error = glGetError(); // get GL-error 1282 to clear glGetError

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined(_DEBUG) || defined(NDEBUG)
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(windowWidth, windowHeight, "SAG Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw OpenGLException("Failed to create Glfw window and OpenGL render context");
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);



	/*** init mouse and keyboard input ***/
	glfwSetKeyCallback(window, glfwKeyboardCallback);
	glfwSetCursorPosCallback(window, glfwMouseCallback);
	// disable mouse cursor so we can reset it to the center after it moved
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// set cursor pos to center of screen for mouse movement
	glfwSetCursorPos(window, screenCenterX, screenCenterY);
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

void GlfwRenderWindow::update(float deltaTime)
{
	glfwPollEvents();
	fireMouseEvents(deltaTime);
	fireKeyEvents(deltaTime);
	KeyboardEventManager::getInstance().update();
	MouseEventManager::getInstance().update();
}

void GlfwRenderWindow::swapBuffer()
{
	glfwSwapBuffers(window);
}

void GlfwRenderWindow::fireMouseEvents(float deltaTime)
{
	if (!mouseMoved)
		return;
	mouseMoved = false;

	float mouseDeltaX = screenCenterX - mousePosX;
	float mouseDeltaY = screenCenterY - mousePosY;

	MouseEventManager::getInstance().dispatchEvent(std::make_unique<MouseMoveEvent>(deltaTime, mouseDeltaX, mouseDeltaY));
	glfwSetCursorPos(window, screenCenterX, screenCenterY); // reset mouse to center of screen - requires: glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED)
}

void GlfwRenderWindow::fireKeyEvents(float deltaTime)
{
	if (keysDown[GLFW_KEY_W])
	{
		KeyboardEventManager::getInstance().dispatchEvent(std::make_unique<KeyDownEvent>(deltaTime, keyboardHelper::KeyboardKey::w));
	}
	if (keysDown[GLFW_KEY_S])
	{
		KeyboardEventManager::getInstance().dispatchEvent(std::make_unique<KeyDownEvent>(deltaTime, keyboardHelper::KeyboardKey::s));
	}
	if (keysDown[GLFW_KEY_A])
	{
		KeyboardEventManager::getInstance().dispatchEvent(std::make_unique<KeyDownEvent>(deltaTime, keyboardHelper::KeyboardKey::a));
	}
	if (keysDown[GLFW_KEY_D]) {
		KeyboardEventManager::getInstance().dispatchEvent(std::make_unique<KeyDownEvent>(deltaTime, keyboardHelper::KeyboardKey::d));
	}
}
