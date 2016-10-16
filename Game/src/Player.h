#ifndef SAGAME_PLAYER_H
#define SAGAME_PLAYER_H

#include <EventSystem\Event\KeyDownEvent.h>
#include <EventSystem\Event\MouseMoveEvent.h>

#include <Render\Camera\Camera.h>

#include <Render\Scene\SceneNode.h>


namespace sagame
{

class Player
{
public:
	Player(sag::Camera&& camera);

	const sag::Camera& getCamera() const { return camera; }

	void handleKeyDownEvent(sag::KeyDownEvent& e);
	void handleMouseMoveEvent(sag::MouseMoveEvent& e);

	void setPosition(glm::vec3 position);


private:
	sag::Camera camera;
	std::weak_ptr<sag::SceneNode> cameraSceneNode;

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

} // namespace sagame


#endif // SAGAME_PLAYER_H
