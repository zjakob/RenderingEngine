
#include "LightEntity.h"

#include <Render\Scene\SceneManager.h>

#include "LightMaterial.h" // TODO single color glow material
#include "SphereGeometry.h"


using namespace sag;
using namespace sagame;

static constexpr float SPHERE_RADIUS = 0.1f;
static constexpr unsigned int SPHERE_RESOLUTION = 20;

LightEntity::LightEntity() :
	light(LightType::Point),
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

void LightEntity::render(const glm::mat4& view, const glm::mat4& viewProjection, const std::list<Light*>& lights)
{
	// TODO fix: somehow automatically set model matrix to getWorldTransformation
	// TODO automatically rotate attached light
	if (auto lockedTranslationNode = translationNode.lock())
	{
		auto worldModel = lockedTranslationNode->getWorldTransformation();
		glm::mat4 mvp = viewProjection * worldModel;
		material->apply(worldModel, view, mvp, lights);
		geometry->draw();
	}
}

void LightEntity::setPosition(glm::vec3& position)
{
	if (auto lockedSceneNode = translationNode.lock())
	{
		auto localMat = lockedSceneNode->getLocalTransformation();
		auto modelMat = glm::translate(localMat, position);
		lockedSceneNode->setLocalTransformation(modelMat);
	}
}

void LightEntity::rotate(float angle, glm::vec3& rotationAxis)
{
	if (auto lockedSceneNode = rotationNode.lock())
	{
		auto localMat = lockedSceneNode->getLocalTransformation();
		auto modelMat = glm::rotate(localMat, angle, rotationAxis);
		lockedSceneNode->setLocalTransformation(modelMat);
	}
}