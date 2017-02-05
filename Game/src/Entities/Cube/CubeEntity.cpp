
#include "CubeEntity.h"

#include <Scene/SceneManager.h>

#include "CubeMaterial.h"
#include "CubeGeometry.h"


using namespace sag;
using namespace sagame;

CubeEntity::CubeEntity() :
	RenderableObject(
		std::move(std::make_unique<CubeMaterial>()),
		std::move(std::make_unique<CubeGeometry>()))
{
	sceneNode = SceneManager::getInstance().getRootSceneNode().lock()->createChildSceneNode();
	if (auto lockedSceneNode = sceneNode.lock())
	{
		lockedSceneNode->attachObject(*this);
	}
}

void CubeEntity::render(const glm::mat4& view, const glm::mat4& viewProjection, const std::list<Light*>& lights, sag::RenderPassData* renderPassDataExchange)
{
	glm::mat4 mvp = viewProjection * modelMatrix;
	material->apply(modelMatrix, view, mvp, lights, renderPassDataExchange);
	geometry->draw();
}

void CubeEntity::setPosition(const glm::vec3& position)
{
	if (auto lockedSceneNode = sceneNode.lock())
	{
		auto localMat = lockedSceneNode->getLocalTransformation();
		auto modelMat = glm::translate(localMat, position);
		lockedSceneNode->setLocalTransformation(modelMat);
	}
}