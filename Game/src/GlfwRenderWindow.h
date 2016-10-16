#ifndef SAGAME_GLFW_RENDER_WINDOW_H
#define SAGAME_GLFW_RENDER_WINDOW_H

#include <GLFW/glfw3.h>

#include <Render\Renderer\RenderWindow.h>


namespace sagame
{

class GlfwRenderWindow : public sag::RenderWindow
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

} // namespace sagame


#endif // SAGAME_GLFW_RENDER_WINDOW_H
