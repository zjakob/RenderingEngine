#ifndef _SAG_PLAYER_H
#define _SAG_PLAYER_H

#include <EventSystem\Event\KeyDownEvent.h>
#include <EventSystem\Event\MouseMoveEvent.h>

#include <Render\Camera\Camera.h>

#include <Render\Scene\SceneNode.h>

class Player
{
public:
	Player(Camera&& camera);

	const Camera& getCamera() const { return camera; }

	void handleKeyDownEvent(KeyDownEvent& e);
	void handleMouseMoveEvent(MouseMoveEvent& e);

	void setPosition(glm::vec3 position);


private:
	Camera camera;
	std::weak_ptr<SceneNode> cameraSceneNode;

	const float mouseSensitivity;
	const float keySensitivity;

	glm::mat4 view;

	float totalYaw;
	float totalPitch;

	glm::vec3 actualTargetOffset;
	glm::vec3 position;
	glm::vec3 left;
	glm::vec3 targetOffset;
	glm::vec3 up;

	void updateViewMatrix();

};

#endif // _SAG_PLAYER_H
