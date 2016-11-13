
#include <glm\vec3.hpp>

#include <Render\Renderer\OpenGLRenderer.h>
#include <Render\Scene\SceneManager.h>
#include "RenderPasses\RenderToScreenPass.h"
#include "RenderPasses\ShadowMapPass.h"
#include "GlfwRenderWindow.h"

#include ".\Entities\Cube\CubeEntity.h"
#include ".\Entities\Light\DirectionalLightEntity.h"
#include ".\Entities\Floor\FloorEntity.h"
#include ".\Entities\Player.h"

#include <EventSystem\MouseEventManager.h>
#include <EventSystem\KeyboardEventManager.h>

#include <chrono>

using namespace sag;
using namespace sagame;

typedef std::chrono::high_resolution_clock Clock;

int main(void)
{
	GlfwRenderWindow window(1280, 720);

	/*** setup scene ***/
	Camera mainCamera(window.getWidth() / float(window.getHeight()), 70.0f);
	Player player(std::move(mainCamera));
	player.setPosition(glm::vec3(0.0f, 1.0f, 1.0f));

	SceneManager& sceneManager = SceneManager::getInstance();
	sceneManager.setMainCamera(player.getCamera());

	OpenGLRenderer renderer(window);
	float shadowMapWidth = 1024.0f;
	float shadowMapHeight = 1024.0f;
	ShadowMapPass shadowMapPass(shadowMapWidth, shadowMapHeight);
	renderer.addRenderPass(&shadowMapPass);
	RenderToScreenPass standardPass(window.getWidth(), window.getHeight());
	renderer.addRenderPass(&standardPass);
	
	DirectionalLightEntity directionalLightEntity(glm::vec3(0.0f), player.getCamera().getFovy(), shadowMapWidth / shadowMapHeight);
	sceneManager.registerRenderableObject(directionalLightEntity);
	sceneManager.registerLight(directionalLightEntity.getLight());
	directionalLightEntity.setPosition(glm::vec3(2.8f, 2.3f, 0.0f));
	float lightRotationAngle = glm::radians(45.0f);
	glm::vec3 lightRotationAxis(0.0f, 1.0f, 0.0f);

	CubeEntity cube;
	sceneManager.registerRenderableObject(cube);
	cube.setPosition(glm::vec3(0.0f, 0.5f, 0.0f));

	FloorEntity floor;
	sceneManager.registerRenderableObject(floor);
	floor.scale(glm::vec3(6.5f, 0.01f, 6.5f));
	floor.setPosition(glm::vec3(0.0f, -0.05f, 0.0f));

	/*** attach input handlers ***/
	KeyboardEventManager::getInstance().addEventCallback(std::bind(&Player::handleKeyDownEvent, &player, std::placeholders::_1));
	MouseEventManager::getInstance().addEventCallback(std::bind(&Player::handleMouseMoveEvent, &player, std::placeholders::_1));


	auto lastTime = Clock::now();

	while (!window.shouldClose())
	{
		auto currentTime = Clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastTime).count();
		lastTime = currentTime;

		window.update(deltaTime);

		directionalLightEntity.rotate(lightRotationAngle * deltaTime, lightRotationAxis);
		
		renderer.render(sceneManager);
	}

	return 0;
}
