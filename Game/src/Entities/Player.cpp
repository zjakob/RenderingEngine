
#include "Player.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Scene/SceneManager.h>
#include <util/ioHelper/keyboardHelper.h>


using namespace sag;
using namespace sagame;

constexpr float defaultMouseSensitivity = 110.0f;
constexpr float defaultKeyBoardSensitivity = 8.0f;

Player::Player(Camera&& camera) :
	camera(camera),
	mouseSensitivity(defaultMouseSensitivity),
	keySensitivity(defaultKeyBoardSensitivity),
	targetOffset(0.0f, 0.0f, -1.0f),
	totalYaw(0.0f),
	totalPitch(0.0f),
	up(0.0f, 1.0f, 0.0f)
{
	cameraSceneNode = SceneManager::getInstance().getRootSceneNode().lock()->createChildSceneNode();
	if (auto lockedSceneNode = cameraSceneNode.lock())
	{
		lockedSceneNode->attachObject(this->camera);
	}
	updateViewMatrix();
}

void Player::handleKeyDownEvent(KeyDownEvent& e)
{
	float velocity = keySensitivity * e.getDeltaTime();
	glm::vec3 front = glm::normalize(actualTargetOffset - position);
	front = glm::normalize(actualTargetOffset);

	switch (e.getKey())
	{
	case keyboardHelper::KeyboardKey::a:
		position += left * velocity;
		break;
	case keyboardHelper::KeyboardKey::d:
		position -= left * velocity;
		break;
	case keyboardHelper::KeyboardKey::w:
		position += front * velocity;
		break;
	case keyboardHelper::KeyboardKey::s:
		position -= front * velocity;
		break;
	default:
		break;
	}

	updateViewMatrix();
}

void Player::handleMouseMoveEvent(MouseMoveEvent& e)
{
	float deltaX = glm::radians(e.getDeltaX() * e.getDeltaTime() * mouseSensitivity);
	float deltaY = glm::radians(e.getDeltaY() * e.getDeltaTime() * mouseSensitivity);

	totalYaw += deltaX;
	totalPitch -= deltaY;

	// TODO: get rid of lookAt and use a single quaternion for orientation to avoid limitations
	static const float tippingPoint = glm::radians(89.9f);
	if (totalPitch >= tippingPoint)
		totalPitch = tippingPoint;
	else if (totalPitch <= -tippingPoint)
		totalPitch = -tippingPoint;

	updateViewMatrix();
}

void Player::updateViewMatrix()
{
	static const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::quat yawQuat = glm::angleAxis(totalYaw, worldUp);
	actualTargetOffset = glm::rotate(yawQuat, targetOffset);

	glm::vec3 forward = actualTargetOffset;
	forward = glm::normalize(forward);
	left = glm::cross(worldUp, forward);
	left = glm::normalize(left);

	glm::quat quatPitch = glm::angleAxis(totalPitch, left);
	actualTargetOffset = glm::rotate(quatPitch, actualTargetOffset);

	glm::vec3 target = position + actualTargetOffset;
	view = glm::lookAt(position, target, up);


	if (auto lockedCameraNode = cameraSceneNode.lock())
	{
		lockedCameraNode->setLocalTransformation(view);
	}
}

void Player::setPosition(glm::vec3 position)
{
	this->position = position;
	updateViewMatrix();
}
