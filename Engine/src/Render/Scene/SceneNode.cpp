
#include "SceneNode.h"

#include <cassert>


SceneNode::SceneNode(std::weak_ptr<SceneNode> parent) :
	parent(parent),
	modelMatrix(1.0)
{

}

void SceneNode::attachObject(MoveableObject& obj)
{
	moveabelObjects.push_back(&obj);
}

void SceneNode::removeObject(MoveableObject& obj)
{
	moveabelObjects.remove(&obj);
}

std::weak_ptr<SceneNode> SceneNode::createChildSceneNode()
{
	auto newChild = std::make_shared<SceneNode>(this->shared_from_this());
	childSceneNodes.push_back(newChild);
	return newChild;
}

void SceneNode::attachChildSceneNode(std::weak_ptr<SceneNode> sceneNode)
{
	if (auto lockedSceneNode = sceneNode.lock())
	{
		if (auto lockedParentSceneNode = lockedSceneNode->parent.lock())
		{
			// detaching the node will not invoke the destructor if it is reattached to this before the end of the lock
			lockedParentSceneNode->detachAndDestroyChildSceneNode(lockedSceneNode);
			childSceneNodes.push_back(lockedSceneNode);
			lockedSceneNode->parent = this->shared_from_this();
		}
	}
}

void SceneNode::detachAndDestroyChildSceneNode(std::weak_ptr<SceneNode> sceneNode)
{
	if (auto lockedSceneNode = sceneNode.lock())
	{
		childSceneNodes.remove(lockedSceneNode);
	}
}

void SceneNode::detachAndDestroySceneNode()
{
	if (auto lockedParent = parent.lock())
	{
		// TODO: C++17 adds std::weak_from_this()
		lockedParent->detachAndDestroyChildSceneNode(this->shared_from_this());
	}
}

void SceneNode::updateChildren()
{
	auto worldMatrix = this->getWorldTransformation();
	for (auto& obj : moveabelObjects)
	{
		obj->setTransformation(worldMatrix);
	}
}

void SceneNode::setLocalTransformation(const glm::mat4& matrix)
{
	this->modelMatrix = matrix;
	updateChildren();
}

const glm::mat4& SceneNode::getLocalTransformation() const
{
	return this->modelMatrix;
}

const glm::mat4& SceneNode::getWorldTransformation() const
{
	if (auto parent = this->parent.lock())
		if (parent->parent.expired()) // root-node's parent points to nullptr and is thus expired
			return glm::mat4(1.0f) * this->modelMatrix;
		else
			return parent->getWorldTransformation() * this->modelMatrix;
	else
		assert("SceneNode has no parent and should not be used!");
}
