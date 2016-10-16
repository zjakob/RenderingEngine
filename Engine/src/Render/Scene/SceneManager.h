#ifndef SAG_SCENE_MANAGER_H
#define SAG_SCENE_MANAGER_H

#include <memory>

#include "SceneNode.h"
#include "RenderableObject.h"
#include "../Camera/Camera.h"


namespace sag
{

class SceneManager
{
public:
	static SceneManager& getInstance();

	void setMainCamera(const Camera& camera);
	void registerRenderableObject(RenderableObject& obj);
	void deregisterRenderableObject(RenderableObject& obj);

	std::weak_ptr<SceneNode> getRootSceneNode() const { return rootSceneNode; }
	const Camera& getMainCamera() const { return *mainCamera;  }
	const std::list<RenderableObject*>& getRenderableObjects() const;


private:
	SceneManager();
	SceneManager(const SceneManager& other) = delete;
	SceneManager(SceneManager&& other) = delete;
	SceneManager& operator=(const SceneManager& other) = delete;
	SceneManager& operator=(SceneManager&& other) = delete;
	~SceneManager();


	std::shared_ptr<SceneNode> rootSceneNode;
	const Camera* mainCamera;
	std::list<RenderableObject*> renderableObjects;

};

} // namespace sag


#endif // SAG_SCENE_MANAGER_H
