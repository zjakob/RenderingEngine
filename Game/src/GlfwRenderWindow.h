#ifndef _SAG_GLFW_RENDER_WINDOW_H
#define _SAG_GLFW_RENDER_WINDOW_H

#include <GLFW/glfw3.h>

#include <Render\Renderer\RenderWindow.h>

class GlfwRenderWindow : public RenderWindow
{
public:
	GlfwRenderWindow(unsigned int windowWidth, unsigned int windowHeight);
	 
	~GlfwRenderWindow();

	GLFWwindow* getWindow();

	bool shouldClose();

	unsigned int getWidth() { return windowWidth; }
	unsigned int getHeight() { return windowHeight; }

	void swapBuffer();

private:
	unsigned int windowWidth;
	unsigned int windowHeight;

	GLFWwindow* window;
};

#endif // _SAG_GLFW_RENDER_WINDOW_H
