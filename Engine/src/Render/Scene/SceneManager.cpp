
#include "SceneManager.h"


SceneManager& SceneManager::getInstance()
{
	static SceneManager singletonInstance;
	return singletonInstance;
}

SceneManager::SceneManager() :
	rootSceneNode(std::make_shared<SceneNode>(std::weak_ptr<SceneNode>()))
{

}

SceneManager::~SceneManager() { }

void SceneManager::setMainCamera(const Camera& camera)
{
	mainCamera = &camera;
}

void SceneManager::registerRenderableObject(RenderableObject& obj)
{
	renderableObjects.push_back(&obj);
}

void SceneManager::deregisterRenderableObject(RenderableObject& obj)
{
	renderableObjects.remove(&obj);
}

const std::list<RenderableObject*>& SceneManager::getRenderableObjects() const
{
	return renderableObjects;
}
