
#include "DirectionalLightEntity.h"

#include <Scene\SceneManager.h>

#include "LightMaterial.h"
#include "SphereGeometry.h"


using namespace sag;
using namespace sagame;

static constexpr float SPHERE_RADIUS = 0.05f;
static constexpr unsigned int SPHERE_RESOLUTION = 20;

DirectionalLightEntity::DirectionalLightEntity(glm::vec3 center, float fovyDeg, float aspect) :
	light(center, fovyDeg, aspect),
	RenderableObject(
		std::move(std::make_unique<LightMaterial>()),
		std::move(std::make_unique<SphereGeometry>(SPHERE_RADIUS, SPHERE_RESOLUTION, SPHERE_RESOLUTION)))
{
	rotationNode = SceneManager::getInstance().getRootSceneNode().lock()->createChildSceneNode();
	if (auto lockedRotationNode = rotationNode.lock())
	{
		translationNode = lockedRotationNode->createChildSceneNode();
		if (auto lockedTranslationNode = translationNode.lock())
		{
			lockedTranslationNode->attachObject(*this);
			lockedTranslationNode->attachObject(light);
		}
	}
}

void DirectionalLightEntity::render(const glm::mat4& view, const glm::mat4& viewProjection, const std::list<Light*>& lights, sag::RenderPassData* renderPassDataExchange)
{
	if (auto lockedTranslationNode = translationNode.lock())
	{
		auto worldModel = lockedTranslationNode->getWorldTransformation();
		glm::mat4 mvp = viewProjection * worldModel;
		material->apply(worldModel, view, mvp, lights, renderPassDataExchange);
		geometry->draw();
	}
}

void DirectionalLightEntity::setPosition(glm::vec3& position)
{
	if (auto lockedSceneNode = translationNode.lock())
	{
		auto localMat = lockedSceneNode->getLocalTransformation();
		auto modelMat = glm::translate(localMat, position);
		lockedSceneNode->setLocalTransformation(modelMat);
	}
}

void DirectionalLightEntity::rotate(float angle, glm::vec3& rotationAxis)
{
	if (auto lockedSceneNode = rotationNode.lock())
	{
		auto localMat = lockedSceneNode->getLocalTransformation();
		auto modelMat = glm::rotate(localMat, angle, rotationAxis);
		lockedSceneNode->setLocalTransformation(modelMat);
	}
}