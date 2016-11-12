
#include "FloorEntity.h"

#include <Render\Scene\SceneManager.h>

#include "FloorMaterial.h"
#include "FloorGeometry.h"

 
using namespace sag;
using namespace sagame;

FloorEntity::FloorEntity() :
	RenderableObject(
		std::move(std::make_unique<FloorMaterial>()),
		std::move(std::make_unique<FloorGeometry>()))
{
	sceneNode = SceneManager::getInstance().getRootSceneNode().lock()->createChildSceneNode();
	if (auto lockedSceneNode = sceneNode.lock())
	{
		lockedSceneNode->attachObject(*this);
	}
}

void FloorEntity::render(const glm::mat4& view, const glm::mat4& viewProjection, const std::list<Light*>& lights, sag::RenderPassData* renderPassDataExchange)
{
	glm::mat4 mvp = viewProjection * modelMatrix;
	material->apply(modelMatrix, view, mvp, lights, renderPassDataExchange);
	geometry->draw();
}

void FloorEntity::setPosition(glm::vec3& position)
{
	if (auto lockedSceneNode = sceneNode.lock())
	{
		auto localMat = lockedSceneNode->getLocalTransformation();
		auto modelMat = glm::translate(localMat, position);
		lockedSceneNode->setLocalTransformation(modelMat);
	}
}

void FloorEntity::scale(glm::vec3& scale)
{

	if (auto lockedSceneNode = sceneNode.lock())
	{
		auto localMat = lockedSceneNode->getLocalTransformation();
		auto modelMat = glm::scale(localMat, scale);
		lockedSceneNode->setLocalTransformation(modelMat);
	}
}
