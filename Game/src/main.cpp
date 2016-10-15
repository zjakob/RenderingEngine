
#include <fstream>
#include <string>
#include <sstream>

#include <iostream>

#include <memory>


//#include <EventSystem\EventSystem.h>
#include <EventSystem\EventManager.h>
#include <EventSystem\Dispatcher\QueuedEventDispatchStrategy.h>
#include <EventSystem\Listener\Strategy\SafeEventCallbackStrategy.h>
#include <EventSystem\Event\KeyDownEvent.h>
#include <EventSystem\Event\MouseMoveEvent.h>

#include <util\ioHelper\keyboardHelper.h>

#include <glm\vec3.hpp> // glm::vec3
#include <glm\gtc\matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm\gtc\type_ptr.hpp> // glm::value_ptr

#include <Render\Renderer\OpenGLRenderer.h>
#include <Render\Scene\SceneManager.h>

#include "GlfwRenderWindow.h"
#include "Player.h"
#include "CubeEntity.h"

double lastTime;
double currentTime;
float deltaTime;

constexpr int windowWidth = 1280;
constexpr int windowHeight = 720;
constexpr float screenCenterX = windowWidth / 2.0f;
constexpr float screenCenterY = windowHeight / 2.0f;

EventManager<
	KeyDownEvent,
	SafeEventCallbackStrategy<KeyDownEvent>,
	QueuedEventDispatchStrategy<KeyDownEvent, SafeEventCallbackStrategy<KeyDownEvent> > > keyDownManager;

EventManager<
	MouseMoveEvent,
	SafeEventCallbackStrategy<MouseMoveEvent>,
	QueuedEventDispatchStrategy<MouseMoveEvent, SafeEventCallbackStrategy<MouseMoveEvent> > > mouseMoveManager;


bool keys[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}
void do_movement()
{
	keyboardHelper::KeyboardKey pressedKey;
	if (keys[GLFW_KEY_W]) 
	{
		pressedKey = keyboardHelper::KeyboardKey::w;
		keyDownManager.dispatchEvent(std::make_unique<KeyDownEvent>(deltaTime, pressedKey));
	}
	if (keys[GLFW_KEY_S]) {
		pressedKey = keyboardHelper::KeyboardKey::s;
		keyDownManager.dispatchEvent(std::make_unique<KeyDownEvent>(deltaTime, pressedKey));
	}
	if (keys[GLFW_KEY_A])
	{
		pressedKey = keyboardHelper::KeyboardKey::a;
		keyDownManager.dispatchEvent(std::make_unique<KeyDownEvent>(deltaTime, pressedKey));
	}
	if (keys[GLFW_KEY_D]) {
		pressedKey = keyboardHelper::KeyboardKey::d;
		keyDownManager.dispatchEvent(std::make_unique<KeyDownEvent>(deltaTime, pressedKey));
	}
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	double deltaX = screenCenterX - xpos;
	double deltaY = screenCenterY - ypos;
	mouseMoveManager.dispatchEvent(std::make_unique<MouseMoveEvent>(deltaTime, deltaX, deltaY));
	// reset mouse to center of screen - requires: glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED)
	glfwSetCursorPos(window, screenCenterX, screenCenterY);
}

int main(void)
{
	GlfwRenderWindow window(windowWidth, windowHeight);

	glfwSetKeyCallback(window.getWindow(), key_callback);
	glfwSetCursorPosCallback(window.getWindow(), cursor_pos_callback);

	// disable mouse cursor so we can reset it to the center after it moved
	glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// set cursor pos to center of screen for mouse movement
	glfwSetCursorPos(window.getWindow(), screenCenterX, screenCenterY);

	Camera mainCamera(windowWidth / float(windowHeight), 90.0f);

	Player player(std::move(mainCamera));
	player.setPosition(glm::vec3(0.0f, 0.0f, 1.0f));

	SceneManager& sceneManager = SceneManager::getInstance();
	sceneManager.setMainCamera(player.getCamera());

	OpenGLRenderer renderer(window);

	// TODO: encapsulate into "InputManager"
	keyDownManager.addEventCallback<KeyDownEvent>(std::bind(&Player::handleKeyDownEvent, &player, std::placeholders::_1));
	mouseMoveManager.addEventCallback<MouseMoveEvent>(std::bind(&Player::handleMouseMoveEvent, &player, std::placeholders::_1));

	CubeEntity cube;
	sceneManager.registerRenderableObject(cube);
	cube.setPosition(glm::vec3(0.0f, 0.0f, -1.0f));

	while (!window.shouldClose())
	{
		currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;

		glfwPollEvents();
		//glfwWaitEvents();
		do_movement();
		keyDownManager.update();
		mouseMoveManager.update();

		
		renderer.render(sceneManager.getRenderableObjects(), sceneManager.getMainCamera());
	}

	
	return 0;
}
