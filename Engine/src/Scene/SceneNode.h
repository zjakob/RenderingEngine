#ifndef SAG_SCENE_NODE_H
#define SAG_SCENE_NODE_H

#include <memory>
#include <list>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <unordered_map>

#include "MoveableObject.h"
#include "../Render/RenderableObject.h"
#include "../util/ComparableObject.h"


namespace sag
{

class SceneNode : public ComparableObject, public std::enable_shared_from_this<SceneNode>
{
public:
	SceneNode(std::weak_ptr<SceneNode> parent);

	void attachObject(MoveableObject& obj);
	void removeObject(MoveableObject& obj);

	std::weak_ptr<SceneNode> createChildSceneNode();
	void attachChildSceneNode(std::weak_ptr<SceneNode> sceneNode);
	void detachAndDestroyChildSceneNode(std::weak_ptr<SceneNode> sceneNode);
	void detachAndDestroySceneNode();

	void setLocalTransformation(const glm::mat4& modelMatrix);
	const glm::mat4 getLocalTransformation() const;
	const glm::mat4 getWorldTransformation() const;

private:
	
	/*
	 * In order to emphasise that the lifetime of the children is managed by the parent node,
	 * a unique pointer could be used instead of the shared_ptr
	 * and children could be accessed from outside via a const raw-pointer or a std::experimental::observer_ptr
	 */
	std::weak_ptr<SceneNode> parent;
	std::list<std::shared_ptr<SceneNode>> childSceneNodes;
	std::list<MoveableObject*> moveabelObjects;

	glm::mat4 modelMatrix;

	void updateChildren();

};

} // namespace sag


#endif // SAG_SCENE_NODE_H
